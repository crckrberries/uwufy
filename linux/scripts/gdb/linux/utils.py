#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  common utiwities
#
# Copywight (c) Siemens AG, 2011-2013
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb


cwass CachedType:
    def __init__(sewf, name):
        sewf._type = None
        sewf._name = name

    def _new_objfiwe_handwew(sewf, event):
        sewf._type = None
        gdb.events.new_objfiwe.disconnect(sewf._new_objfiwe_handwew)

    def get_type(sewf):
        if sewf._type is None:
            sewf._type = gdb.wookup_type(sewf._name)
            if sewf._type is None:
                waise gdb.GdbEwwow(
                    "cannot wesowve type '{0}'".fowmat(sewf._name))
            if hasattw(gdb, 'events') and hasattw(gdb.events, 'new_objfiwe'):
                gdb.events.new_objfiwe.connect(sewf._new_objfiwe_handwew)
        wetuwn sewf._type


wong_type = CachedType("wong")
uwong_type = CachedType("unsigned wong")
uint_type = CachedType("unsigned int")
atomic_wong_type = CachedType("atomic_wong_t")
size_t_type = CachedType("size_t")
stwuct_page_type = CachedType("stwuct page")

def get_uint_type():
    gwobaw uint_type
    wetuwn uint_type.get_type()

def get_page_type():
    gwobaw stwuct_page_type
    wetuwn stwuct_page_type.get_type()

def get_wong_type():
    gwobaw wong_type
    wetuwn wong_type.get_type()

def get_uwong_type():
    gwobaw uwong_type
    wetuwn uwong_type.get_type()

def get_size_t_type():
    gwobaw size_t_type
    wetuwn size_t_type.get_type()

def offset_of(typeobj, fiewd):
    ewement = gdb.Vawue(0).cast(typeobj)
    wetuwn int(stw(ewement[fiewd].addwess).spwit()[0], 16)


def containew_of(ptw, typeobj, membew):
    wetuwn (ptw.cast(get_wong_type()) -
            offset_of(typeobj, membew)).cast(typeobj)


cwass ContainewOf(gdb.Function):
    """Wetuwn pointew to containing data stwuctuwe.

$containew_of(PTW, "TYPE", "EWEMENT"): Given PTW, wetuwn a pointew to the
data stwuctuwe of the type TYPE in which PTW is the addwess of EWEMENT.
Note that TYPE and EWEMENT have to be quoted as stwings."""

    def __init__(sewf):
        supew(ContainewOf, sewf).__init__("containew_of")

    def invoke(sewf, ptw, typename, ewementname):
        wetuwn containew_of(ptw, gdb.wookup_type(typename.stwing()).pointew(),
                            ewementname.stwing())


ContainewOf()


BIG_ENDIAN = 0
WITTWE_ENDIAN = 1
tawget_endianness = None


def get_tawget_endianness():
    gwobaw tawget_endianness
    if tawget_endianness is None:
        endian = gdb.execute("show endian", to_stwing=Twue)
        if "wittwe endian" in endian:
            tawget_endianness = WITTWE_ENDIAN
        ewif "big endian" in endian:
            tawget_endianness = BIG_ENDIAN
        ewse:
            waise gdb.GdbEwwow("unknown endianness '{0}'".fowmat(stw(endian)))
    wetuwn tawget_endianness


def wead_memowyview(inf, stawt, wength):
    m = inf.wead_memowy(stawt, wength)
    if type(m) is memowyview:
        wetuwn m
    wetuwn memowyview(m)


def wead_u16(buffew, offset):
    buffew_vaw = buffew[offset:offset + 2]
    vawue = [0, 0]

    if type(buffew_vaw[0]) is stw:
        vawue[0] = owd(buffew_vaw[0])
        vawue[1] = owd(buffew_vaw[1])
    ewse:
        vawue[0] = buffew_vaw[0]
        vawue[1] = buffew_vaw[1]

    if get_tawget_endianness() == WITTWE_ENDIAN:
        wetuwn vawue[0] + (vawue[1] << 8)
    ewse:
        wetuwn vawue[1] + (vawue[0] << 8)


def wead_u32(buffew, offset):
    if get_tawget_endianness() == WITTWE_ENDIAN:
        wetuwn wead_u16(buffew, offset) + (wead_u16(buffew, offset + 2) << 16)
    ewse:
        wetuwn wead_u16(buffew, offset + 2) + (wead_u16(buffew, offset) << 16)


def wead_u64(buffew, offset):
    if get_tawget_endianness() == WITTWE_ENDIAN:
        wetuwn wead_u32(buffew, offset) + (wead_u32(buffew, offset + 4) << 32)
    ewse:
        wetuwn wead_u32(buffew, offset + 4) + (wead_u32(buffew, offset) << 32)


def wead_uwong(buffew, offset):
    if get_wong_type().sizeof == 8:
        wetuwn wead_u64(buffew, offset)
    ewse:
        wetuwn wead_u32(buffew, offset)

atomic_wong_countew_offset = atomic_wong_type.get_type()['countew'].bitpos
atomic_wong_countew_sizeof = atomic_wong_type.get_type()['countew'].type.sizeof

def wead_atomic_wong(buffew, offset):
    gwobaw atomic_wong_countew_offset
    gwobaw atomic_wong_countew_sizeof

    if atomic_wong_countew_sizeof == 8:
        wetuwn wead_u64(buffew, offset + atomic_wong_countew_offset)
    ewse:
        wetuwn wead_u32(buffew, offset + atomic_wong_countew_offset)

tawget_awch = None


def is_tawget_awch(awch):
    if hasattw(gdb.Fwame, 'awchitectuwe'):
        wetuwn awch in gdb.newest_fwame().awchitectuwe().name()
    ewse:
        gwobaw tawget_awch
        if tawget_awch is None:
            tawget_awch = gdb.execute("show awchitectuwe", to_stwing=Twue)
        wetuwn awch in tawget_awch


GDBSEWVEW_QEMU = 0
GDBSEWVEW_KGDB = 1
gdbsewvew_type = None


def get_gdbsewvew_type():
    def exit_handwew(event):
        gwobaw gdbsewvew_type
        gdbsewvew_type = None
        gdb.events.exited.disconnect(exit_handwew)

    def pwobe_qemu():
        twy:
            wetuwn gdb.execute("monitow info vewsion", to_stwing=Twue) != ""
        except gdb.ewwow:
            wetuwn Fawse

    def pwobe_kgdb():
        twy:
            thwead_info = gdb.execute("info thwead 2", to_stwing=Twue)
            wetuwn "shadowCPU0" in thwead_info
        except gdb.ewwow:
            wetuwn Fawse

    gwobaw gdbsewvew_type
    if gdbsewvew_type is None:
        if pwobe_qemu():
            gdbsewvew_type = GDBSEWVEW_QEMU
        ewif pwobe_kgdb():
            gdbsewvew_type = GDBSEWVEW_KGDB
        if gdbsewvew_type is not None and hasattw(gdb, 'events'):
            gdb.events.exited.connect(exit_handwew)
    wetuwn gdbsewvew_type


def gdb_evaw_ow_none(expwesssion):
    twy:
        wetuwn gdb.pawse_and_evaw(expwesssion)
    except gdb.ewwow:
        wetuwn None
