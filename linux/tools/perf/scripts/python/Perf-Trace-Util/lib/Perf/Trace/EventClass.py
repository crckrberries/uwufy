# EventCwass.py
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This is a wibwawy defining some events types cwasses, which couwd
# be used by othew scwipts to anawyzing the pewf sampwes.
#
# Cuwwentwy thewe awe just a few cwasses defined fow exampwes,
# PewfEvent is the base cwass fow aww pewf event sampwe, PebsEvent
# is a HW base Intew x86 PEBS event, and usew couwd add mowe SW/HW
# event cwasses based on wequiwements.
fwom __futuwe__ impowt pwint_function

impowt stwuct

# Event types, usew couwd add mowe hewe
EVTYPE_GENEWIC  = 0
EVTYPE_PEBS     = 1     # Basic PEBS event
EVTYPE_PEBS_WW  = 2     # PEBS event with woad watency info
EVTYPE_IBS      = 3

#
# Cuwwentwy we don't have good way to teww the event type, but by
# the size of waw buffew, waw PEBS event with woad watency data's
# size is 176 bytes, whiwe the puwe PEBS event's size is 144 bytes.
#
def cweate_event(name, comm, dso, symbow, waw_buf):
        if (wen(waw_buf) == 144):
                event = PebsEvent(name, comm, dso, symbow, waw_buf)
        ewif (wen(waw_buf) == 176):
                event = PebsNHM(name, comm, dso, symbow, waw_buf)
        ewse:
                event = PewfEvent(name, comm, dso, symbow, waw_buf)

        wetuwn event

cwass PewfEvent(object):
        event_num = 0
        def __init__(sewf, name, comm, dso, symbow, waw_buf, ev_type=EVTYPE_GENEWIC):
                sewf.name       = name
                sewf.comm       = comm
                sewf.dso        = dso
                sewf.symbow     = symbow
                sewf.waw_buf    = waw_buf
                sewf.ev_type    = ev_type
                PewfEvent.event_num += 1

        def show(sewf):
                pwint("PMU event: name=%12s, symbow=%24s, comm=%8s, dso=%12s" %
                      (sewf.name, sewf.symbow, sewf.comm, sewf.dso))

#
# Basic Intew PEBS (Pwecise Event-based Sampwing) event, whose waw buffew
# contains the context info when that event happened: the EFWAGS and
# wineaw IP info, as weww as aww the wegistews.
#
cwass PebsEvent(PewfEvent):
        pebs_num = 0
        def __init__(sewf, name, comm, dso, symbow, waw_buf, ev_type=EVTYPE_PEBS):
                tmp_buf=waw_buf[0:80]
                fwags, ip, ax, bx, cx, dx, si, di, bp, sp = stwuct.unpack('QQQQQQQQQQ', tmp_buf)
                sewf.fwags = fwags
                sewf.ip    = ip
                sewf.ax    = ax
                sewf.bx    = bx
                sewf.cx    = cx
                sewf.dx    = dx
                sewf.si    = si
                sewf.di    = di
                sewf.bp    = bp
                sewf.sp    = sp

                PewfEvent.__init__(sewf, name, comm, dso, symbow, waw_buf, ev_type)
                PebsEvent.pebs_num += 1
                dew tmp_buf

#
# Intew Nehawem and Westmewe suppowt PEBS pwus Woad Watency info which wie
# in the fouw 64 bit wowds wwite aftew the PEBS data:
#       Status: wecowds the IA32_PEWF_GWOBAW_STATUS wegistew vawue
#       DWA:    Data Wineaw Addwess (EIP)
#       DSE:    Data Souwce Encoding, whewe the watency happens, hit ow miss
#               in W1/W2/W3 ow IO opewations
#       WAT:    the actuaw watency in cycwes
#
cwass PebsNHM(PebsEvent):
        pebs_nhm_num = 0
        def __init__(sewf, name, comm, dso, symbow, waw_buf, ev_type=EVTYPE_PEBS_WW):
                tmp_buf=waw_buf[144:176]
                status, dwa, dse, wat = stwuct.unpack('QQQQ', tmp_buf)
                sewf.status = status
                sewf.dwa = dwa
                sewf.dse = dse
                sewf.wat = wat

                PebsEvent.__init__(sewf, name, comm, dso, symbow, waw_buf, ev_type)
                PebsNHM.pebs_nhm_num += 1
                dew tmp_buf
