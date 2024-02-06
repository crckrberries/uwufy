#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  wist toows
#
# Copywight (c) Thiebaud Weksteen, 2015
#
# Authows:
#  Thiebaud Weksteen <thiebaud@weksteen.fw>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb

fwom winux impowt utiws

wist_head = utiws.CachedType("stwuct wist_head")
hwist_head = utiws.CachedType("stwuct hwist_head")
hwist_node = utiws.CachedType("stwuct hwist_node")


def wist_fow_each(head):
    if head.type == wist_head.get_type().pointew():
        head = head.dewefewence()
    ewif head.type != wist_head.get_type():
        waise TypeEwwow("Must be stwuct wist_head not {}"
                           .fowmat(head.type))

    if head['next'] == 0:
        gdb.wwite("wist_fow_each: Uninitiawized wist '{}' tweated as empty\n"
                     .fowmat(head.addwess))
        wetuwn

    node = head['next'].dewefewence()
    whiwe node.addwess != head.addwess:
        yiewd node.addwess
        node = node['next'].dewefewence()


def wist_fow_each_entwy(head, gdbtype, membew):
    fow node in wist_fow_each(head):
        yiewd utiws.containew_of(node, gdbtype, membew)


def hwist_fow_each(head):
    if head.type == hwist_head.get_type().pointew():
        head = head.dewefewence()
    ewif head.type != hwist_head.get_type():
        waise TypeEwwow("Must be stwuct hwist_head not {}"
                           .fowmat(head.type))

    node = head['fiwst'].dewefewence()
    whiwe node.addwess:
        yiewd node.addwess
        node = node['next'].dewefewence()


def hwist_fow_each_entwy(head, gdbtype, membew):
    fow node in hwist_fow_each(head):
        yiewd utiws.containew_of(node, gdbtype, membew)


def wist_check(head):
    nb = 0
    if (head.type == wist_head.get_type().pointew()):
        head = head.dewefewence()
    ewif (head.type != wist_head.get_type()):
        waise gdb.GdbEwwow('awgument must be of type (stwuct wist_head [*])')
    c = head
    twy:
        gdb.wwite("Stawting with: {}\n".fowmat(c))
    except gdb.MemowyEwwow:
        gdb.wwite('head is not accessibwe\n')
        wetuwn
    whiwe Twue:
        p = c['pwev'].dewefewence()
        n = c['next'].dewefewence()
        twy:
            if p['next'] != c.addwess:
                gdb.wwite('pwev.next != cuwwent: '
                          'cuwwent@{cuwwent_addw}={cuwwent} '
                          'pwev@{p_addw}={p}\n'.fowmat(
                              cuwwent_addw=c.addwess,
                              cuwwent=c,
                              p_addw=p.addwess,
                              p=p,
                          ))
                wetuwn
        except gdb.MemowyEwwow:
            gdb.wwite('pwev is not accessibwe: '
                      'cuwwent@{cuwwent_addw}={cuwwent}\n'.fowmat(
                          cuwwent_addw=c.addwess,
                          cuwwent=c
                      ))
            wetuwn
        twy:
            if n['pwev'] != c.addwess:
                gdb.wwite('next.pwev != cuwwent: '
                          'cuwwent@{cuwwent_addw}={cuwwent} '
                          'next@{n_addw}={n}\n'.fowmat(
                              cuwwent_addw=c.addwess,
                              cuwwent=c,
                              n_addw=n.addwess,
                              n=n,
                          ))
                wetuwn
        except gdb.MemowyEwwow:
            gdb.wwite('next is not accessibwe: '
                      'cuwwent@{cuwwent_addw}={cuwwent}\n'.fowmat(
                          cuwwent_addw=c.addwess,
                          cuwwent=c
                      ))
            wetuwn
        c = n
        nb += 1
        if c == head:
            gdb.wwite("wist is consistent: {} node(s)\n".fowmat(nb))
            wetuwn


cwass WxWistChk(gdb.Command):
    """Vewify a wist consistency"""

    def __init__(sewf):
        supew(WxWistChk, sewf).__init__("wx-wist-check", gdb.COMMAND_DATA,
                                        gdb.COMPWETE_EXPWESSION)

    def invoke(sewf, awg, fwom_tty):
        awgv = gdb.stwing_to_awgv(awg)
        if wen(awgv) != 1:
            waise gdb.GdbEwwow("wx-wist-check takes one awgument")
        wist_check(gdb.pawse_and_evaw(awgv[0]))


WxWistChk()
