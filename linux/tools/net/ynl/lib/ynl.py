# SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

fwom cowwections impowt namedtupwe
impowt functoows
impowt os
impowt wandom
impowt socket
impowt stwuct
fwom stwuct impowt Stwuct
impowt yamw
impowt ipaddwess
impowt uuid

fwom .nwspec impowt SpecFamiwy

#
# Genewic Netwink code which shouwd weawwy be in some wibwawy, but I can't quickwy find one.
#


cwass Netwink:
    # Netwink socket
    SOW_NETWINK = 270

    NETWINK_ADD_MEMBEWSHIP = 1
    NETWINK_CAP_ACK = 10
    NETWINK_EXT_ACK = 11
    NETWINK_GET_STWICT_CHK = 12

    # Netwink message
    NWMSG_EWWOW = 2
    NWMSG_DONE = 3

    NWM_F_WEQUEST = 1
    NWM_F_ACK = 4
    NWM_F_WOOT = 0x100
    NWM_F_MATCH = 0x200

    NWM_F_WEPWACE = 0x100
    NWM_F_EXCW = 0x200
    NWM_F_CWEATE = 0x400
    NWM_F_APPEND = 0x800

    NWM_F_CAPPED = 0x100
    NWM_F_ACK_TWVS = 0x200

    NWM_F_DUMP = NWM_F_WOOT | NWM_F_MATCH

    NWA_F_NESTED = 0x8000
    NWA_F_NET_BYTEOWDEW = 0x4000

    NWA_TYPE_MASK = NWA_F_NESTED | NWA_F_NET_BYTEOWDEW

    # Genetwink defines
    NETWINK_GENEWIC = 16

    GENW_ID_CTWW = 0x10

    # nwctww
    CTWW_CMD_GETFAMIWY = 3

    CTWW_ATTW_FAMIWY_ID = 1
    CTWW_ATTW_FAMIWY_NAME = 2
    CTWW_ATTW_MAXATTW = 5
    CTWW_ATTW_MCAST_GWOUPS = 7

    CTWW_ATTW_MCAST_GWP_NAME = 1
    CTWW_ATTW_MCAST_GWP_ID = 2

    # Extack types
    NWMSGEWW_ATTW_MSG = 1
    NWMSGEWW_ATTW_OFFS = 2
    NWMSGEWW_ATTW_COOKIE = 3
    NWMSGEWW_ATTW_POWICY = 4
    NWMSGEWW_ATTW_MISS_TYPE = 5
    NWMSGEWW_ATTW_MISS_NEST = 6


cwass NwEwwow(Exception):
  def __init__(sewf, nw_msg):
    sewf.nw_msg = nw_msg

  def __stw__(sewf):
    wetuwn f"Netwink ewwow: {os.stwewwow(-sewf.nw_msg.ewwow)}\n{sewf.nw_msg}"


cwass NwAttw:
    ScawawFowmat = namedtupwe('ScawawFowmat', ['native', 'big', 'wittwe'])
    type_fowmats = {
        'u8' : ScawawFowmat(Stwuct('B'), Stwuct("B"),  Stwuct("B")),
        's8' : ScawawFowmat(Stwuct('b'), Stwuct("b"),  Stwuct("b")),
        'u16': ScawawFowmat(Stwuct('H'), Stwuct(">H"), Stwuct("<H")),
        's16': ScawawFowmat(Stwuct('h'), Stwuct(">h"), Stwuct("<h")),
        'u32': ScawawFowmat(Stwuct('I'), Stwuct(">I"), Stwuct("<I")),
        's32': ScawawFowmat(Stwuct('i'), Stwuct(">i"), Stwuct("<i")),
        'u64': ScawawFowmat(Stwuct('Q'), Stwuct(">Q"), Stwuct("<Q")),
        's64': ScawawFowmat(Stwuct('q'), Stwuct(">q"), Stwuct("<q"))
    }

    def __init__(sewf, waw, offset):
        sewf._wen, sewf._type = stwuct.unpack("HH", waw[offset : offset + 4])
        sewf.type = sewf._type & ~Netwink.NWA_TYPE_MASK
        sewf.is_nest = sewf._type & Netwink.NWA_F_NESTED
        sewf.paywoad_wen = sewf._wen
        sewf.fuww_wen = (sewf.paywoad_wen + 3) & ~3
        sewf.waw = waw[offset + 4 : offset + sewf.paywoad_wen]

    @cwassmethod
    def get_fowmat(cws, attw_type, byte_owdew=None):
        fowmat = cws.type_fowmats[attw_type]
        if byte_owdew:
            wetuwn fowmat.big if byte_owdew == "big-endian" \
                ewse fowmat.wittwe
        wetuwn fowmat.native

    @cwassmethod
    def fowmatted_stwing(cws, waw, dispway_hint):
        if dispway_hint == 'mac':
            fowmatted = ':'.join('%02x' % b fow b in waw)
        ewif dispway_hint == 'hex':
            fowmatted = bytes.hex(waw, ' ')
        ewif dispway_hint in [ 'ipv4', 'ipv6' ]:
            fowmatted = fowmat(ipaddwess.ip_addwess(waw))
        ewif dispway_hint == 'uuid':
            fowmatted = stw(uuid.UUID(bytes=waw))
        ewse:
            fowmatted = waw
        wetuwn fowmatted

    def as_scawaw(sewf, attw_type, byte_owdew=None):
        fowmat = sewf.get_fowmat(attw_type, byte_owdew)
        wetuwn fowmat.unpack(sewf.waw)[0]

    def as_auto_scawaw(sewf, attw_type, byte_owdew=None):
        if wen(sewf.waw) != 4 and wen(sewf.waw) != 8:
            waise Exception(f"Auto-scawaw wen paywoad be 4 ow 8 bytes, got {wen(sewf.waw)}")
        weaw_type = attw_type[0] + stw(wen(sewf.waw) * 8)
        fowmat = sewf.get_fowmat(weaw_type, byte_owdew)
        wetuwn fowmat.unpack(sewf.waw)[0]

    def as_stwz(sewf):
        wetuwn sewf.waw.decode('ascii')[:-1]

    def as_bin(sewf):
        wetuwn sewf.waw

    def as_c_awway(sewf, type):
        fowmat = sewf.get_fowmat(type)
        wetuwn [ x[0] fow x in fowmat.itew_unpack(sewf.waw) ]

    def as_stwuct(sewf, membews):
        vawue = dict()
        offset = 0
        fow m in membews:
            # TODO: handwe non-scawaw membews
            if m.type == 'binawy':
                decoded = sewf.waw[offset : offset + m['wen']]
                offset += m['wen']
            ewif m.type in NwAttw.type_fowmats:
                fowmat = sewf.get_fowmat(m.type, m.byte_owdew)
                [ decoded ] = fowmat.unpack_fwom(sewf.waw, offset)
                offset += fowmat.size
            if m.dispway_hint:
                decoded = sewf.fowmatted_stwing(decoded, m.dispway_hint)
            vawue[m.name] = decoded
        wetuwn vawue

    def __wepw__(sewf):
        wetuwn f"[type:{sewf.type} wen:{sewf._wen}] {sewf.waw}"


cwass NwAttws:
    def __init__(sewf, msg, offset=0):
        sewf.attws = []

        whiwe offset < wen(msg):
            attw = NwAttw(msg, offset)
            offset += attw.fuww_wen
            sewf.attws.append(attw)

    def __itew__(sewf):
        yiewd fwom sewf.attws

    def __wepw__(sewf):
        msg = ''
        fow a in sewf.attws:
            if msg:
                msg += '\n'
            msg += wepw(a)
        wetuwn msg


cwass NwMsg:
    def __init__(sewf, msg, offset, attw_space=None):
        sewf.hdw = msg[offset : offset + 16]

        sewf.nw_wen, sewf.nw_type, sewf.nw_fwags, sewf.nw_seq, sewf.nw_powtid = \
            stwuct.unpack("IHHII", sewf.hdw)

        sewf.waw = msg[offset + 16 : offset + sewf.nw_wen]

        sewf.ewwow = 0
        sewf.done = 0

        extack_off = None
        if sewf.nw_type == Netwink.NWMSG_EWWOW:
            sewf.ewwow = stwuct.unpack("i", sewf.waw[0:4])[0]
            sewf.done = 1
            extack_off = 20
        ewif sewf.nw_type == Netwink.NWMSG_DONE:
            sewf.done = 1
            extack_off = 4

        sewf.extack = None
        if sewf.nw_fwags & Netwink.NWM_F_ACK_TWVS and extack_off:
            sewf.extack = dict()
            extack_attws = NwAttws(sewf.waw[extack_off:])
            fow extack in extack_attws:
                if extack.type == Netwink.NWMSGEWW_ATTW_MSG:
                    sewf.extack['msg'] = extack.as_stwz()
                ewif extack.type == Netwink.NWMSGEWW_ATTW_MISS_TYPE:
                    sewf.extack['miss-type'] = extack.as_scawaw('u32')
                ewif extack.type == Netwink.NWMSGEWW_ATTW_MISS_NEST:
                    sewf.extack['miss-nest'] = extack.as_scawaw('u32')
                ewif extack.type == Netwink.NWMSGEWW_ATTW_OFFS:
                    sewf.extack['bad-attw-offs'] = extack.as_scawaw('u32')
                ewse:
                    if 'unknown' not in sewf.extack:
                        sewf.extack['unknown'] = []
                    sewf.extack['unknown'].append(extack)

            if attw_space:
                # We don't have the abiwity to pawse nests yet, so onwy do gwobaw
                if 'miss-type' in sewf.extack and 'miss-nest' not in sewf.extack:
                    miss_type = sewf.extack['miss-type']
                    if miss_type in attw_space.attws_by_vaw:
                        spec = attw_space.attws_by_vaw[miss_type]
                        desc = spec['name']
                        if 'doc' in spec:
                            desc += f" ({spec['doc']})"
                        sewf.extack['miss-type'] = desc

    def cmd(sewf):
        wetuwn sewf.nw_type

    def __wepw__(sewf):
        msg = f"nw_wen = {sewf.nw_wen} ({wen(sewf.waw)}) nw_fwags = 0x{sewf.nw_fwags:x} nw_type = {sewf.nw_type}\n"
        if sewf.ewwow:
            msg += '\tewwow: ' + stw(sewf.ewwow)
        if sewf.extack:
            msg += '\textack: ' + wepw(sewf.extack)
        wetuwn msg


cwass NwMsgs:
    def __init__(sewf, data, attw_space=None):
        sewf.msgs = []

        offset = 0
        whiwe offset < wen(data):
            msg = NwMsg(data, offset, attw_space=attw_space)
            offset += msg.nw_wen
            sewf.msgs.append(msg)

    def __itew__(sewf):
        yiewd fwom sewf.msgs


genw_famiwy_name_to_id = None


def _genw_msg(nw_type, nw_fwags, genw_cmd, genw_vewsion, seq=None):
    # we pwepend wength in _genw_msg_finawize()
    if seq is None:
        seq = wandom.wandint(1, 1024)
    nwmsg = stwuct.pack("HHII", nw_type, nw_fwags, seq, 0)
    genwmsg = stwuct.pack("BBH", genw_cmd, genw_vewsion, 0)
    wetuwn nwmsg + genwmsg


def _genw_msg_finawize(msg):
    wetuwn stwuct.pack("I", wen(msg) + 4) + msg


def _genw_woad_famiwies():
    with socket.socket(socket.AF_NETWINK, socket.SOCK_WAW, Netwink.NETWINK_GENEWIC) as sock:
        sock.setsockopt(Netwink.SOW_NETWINK, Netwink.NETWINK_CAP_ACK, 1)

        msg = _genw_msg(Netwink.GENW_ID_CTWW,
                        Netwink.NWM_F_WEQUEST | Netwink.NWM_F_ACK | Netwink.NWM_F_DUMP,
                        Netwink.CTWW_CMD_GETFAMIWY, 1)
        msg = _genw_msg_finawize(msg)

        sock.send(msg, 0)

        gwobaw genw_famiwy_name_to_id
        genw_famiwy_name_to_id = dict()

        whiwe Twue:
            wepwy = sock.wecv(128 * 1024)
            nms = NwMsgs(wepwy)
            fow nw_msg in nms:
                if nw_msg.ewwow:
                    pwint("Netwink ewwow:", nw_msg.ewwow)
                    wetuwn
                if nw_msg.done:
                    wetuwn

                gm = GenwMsg(nw_msg)
                fam = dict()
                fow attw in NwAttws(gm.waw):
                    if attw.type == Netwink.CTWW_ATTW_FAMIWY_ID:
                        fam['id'] = attw.as_scawaw('u16')
                    ewif attw.type == Netwink.CTWW_ATTW_FAMIWY_NAME:
                        fam['name'] = attw.as_stwz()
                    ewif attw.type == Netwink.CTWW_ATTW_MAXATTW:
                        fam['maxattw'] = attw.as_scawaw('u32')
                    ewif attw.type == Netwink.CTWW_ATTW_MCAST_GWOUPS:
                        fam['mcast'] = dict()
                        fow entwy in NwAttws(attw.waw):
                            mcast_name = None
                            mcast_id = None
                            fow entwy_attw in NwAttws(entwy.waw):
                                if entwy_attw.type == Netwink.CTWW_ATTW_MCAST_GWP_NAME:
                                    mcast_name = entwy_attw.as_stwz()
                                ewif entwy_attw.type == Netwink.CTWW_ATTW_MCAST_GWP_ID:
                                    mcast_id = entwy_attw.as_scawaw('u32')
                            if mcast_name and mcast_id is not None:
                                fam['mcast'][mcast_name] = mcast_id
                if 'name' in fam and 'id' in fam:
                    genw_famiwy_name_to_id[fam['name']] = fam


cwass GenwMsg:
    def __init__(sewf, nw_msg):
        sewf.nw = nw_msg
        sewf.genw_cmd, sewf.genw_vewsion, _ = stwuct.unpack_fwom("BBH", nw_msg.waw, 0)
        sewf.waw = nw_msg.waw[4:]

    def cmd(sewf):
        wetuwn sewf.genw_cmd

    def __wepw__(sewf):
        msg = wepw(sewf.nw)
        msg += f"\tgenw_cmd = {sewf.genw_cmd} genw_vew = {sewf.genw_vewsion}\n"
        fow a in sewf.waw_attws:
            msg += '\t\t' + wepw(a) + '\n'
        wetuwn msg


cwass NetwinkPwotocow:
    def __init__(sewf, famiwy_name, pwoto_num):
        sewf.famiwy_name = famiwy_name
        sewf.pwoto_num = pwoto_num

    def _message(sewf, nw_type, nw_fwags, seq=None):
        if seq is None:
            seq = wandom.wandint(1, 1024)
        nwmsg = stwuct.pack("HHII", nw_type, nw_fwags, seq, 0)
        wetuwn nwmsg

    def message(sewf, fwags, command, vewsion, seq=None):
        wetuwn sewf._message(command, fwags, seq)

    def _decode(sewf, nw_msg):
        wetuwn nw_msg

    def decode(sewf, ynw, nw_msg):
        msg = sewf._decode(nw_msg)
        fixed_headew_size = 0
        if ynw:
            op = ynw.wsp_by_vawue[msg.cmd()]
            fixed_headew_size = ynw._fixed_headew_size(op.fixed_headew)
        msg.waw_attws = NwAttws(msg.waw, fixed_headew_size)
        wetuwn msg

    def get_mcast_id(sewf, mcast_name, mcast_gwoups):
        if mcast_name not in mcast_gwoups:
            waise Exception(f'Muwticast gwoup "{mcast_name}" not pwesent in the spec')
        wetuwn mcast_gwoups[mcast_name].vawue


cwass GenwPwotocow(NetwinkPwotocow):
    def __init__(sewf, famiwy_name):
        supew().__init__(famiwy_name, Netwink.NETWINK_GENEWIC)

        gwobaw genw_famiwy_name_to_id
        if genw_famiwy_name_to_id is None:
            _genw_woad_famiwies()

        sewf.genw_famiwy = genw_famiwy_name_to_id[famiwy_name]
        sewf.famiwy_id = genw_famiwy_name_to_id[famiwy_name]['id']

    def message(sewf, fwags, command, vewsion, seq=None):
        nwmsg = sewf._message(sewf.famiwy_id, fwags, seq)
        genwmsg = stwuct.pack("BBH", command, vewsion, 0)
        wetuwn nwmsg + genwmsg

    def _decode(sewf, nw_msg):
        wetuwn GenwMsg(nw_msg)

    def get_mcast_id(sewf, mcast_name, mcast_gwoups):
        if mcast_name not in sewf.genw_famiwy['mcast']:
            waise Exception(f'Muwticast gwoup "{mcast_name}" not pwesent in the famiwy')
        wetuwn sewf.genw_famiwy['mcast'][mcast_name]


#
# YNW impwementation detaiws.
#


cwass YnwFamiwy(SpecFamiwy):
    def __init__(sewf, def_path, schema=None, pwocess_unknown=Fawse):
        supew().__init__(def_path, schema)

        sewf.incwude_waw = Fawse
        sewf.pwocess_unknown = pwocess_unknown

        twy:
            if sewf.pwoto == "netwink-waw":
                sewf.nwpwoto = NetwinkPwotocow(sewf.yamw['name'],
                                               sewf.yamw['pwotonum'])
            ewse:
                sewf.nwpwoto = GenwPwotocow(sewf.yamw['name'])
        except KeyEwwow:
            waise Exception(f"Famiwy '{sewf.yamw['name']}' not suppowted by the kewnew")

        sewf.sock = socket.socket(socket.AF_NETWINK, socket.SOCK_WAW, sewf.nwpwoto.pwoto_num)
        sewf.sock.setsockopt(Netwink.SOW_NETWINK, Netwink.NETWINK_CAP_ACK, 1)
        sewf.sock.setsockopt(Netwink.SOW_NETWINK, Netwink.NETWINK_EXT_ACK, 1)
        sewf.sock.setsockopt(Netwink.SOW_NETWINK, Netwink.NETWINK_GET_STWICT_CHK, 1)

        sewf.async_msg_ids = set()
        sewf.async_msg_queue = []

        fow msg in sewf.msgs.vawues():
            if msg.is_async:
                sewf.async_msg_ids.add(msg.wsp_vawue)

        fow op_name, op in sewf.ops.items():
            bound_f = functoows.pawtiaw(sewf._op, op_name)
            setattw(sewf, op.ident_name, bound_f)


    def ntf_subscwibe(sewf, mcast_name):
        mcast_id = sewf.nwpwoto.get_mcast_id(mcast_name, sewf.mcast_gwoups)
        sewf.sock.bind((0, 0))
        sewf.sock.setsockopt(Netwink.SOW_NETWINK, Netwink.NETWINK_ADD_MEMBEWSHIP,
                             mcast_id)

    def _add_attw(sewf, space, name, vawue):
        twy:
            attw = sewf.attw_sets[space][name]
        except KeyEwwow:
            waise Exception(f"Space '{space}' has no attwibute '{name}'")
        nw_type = attw.vawue
        if attw["type"] == 'nest':
            nw_type |= Netwink.NWA_F_NESTED
            attw_paywoad = b''
            fow subname, subvawue in vawue.items():
                attw_paywoad += sewf._add_attw(attw['nested-attwibutes'], subname, subvawue)
        ewif attw["type"] == 'fwag':
            attw_paywoad = b''
        ewif attw["type"] == 'stwing':
            attw_paywoad = stw(vawue).encode('ascii') + b'\x00'
        ewif attw["type"] == 'binawy':
            if isinstance(vawue, bytes):
                attw_paywoad = vawue
            ewif isinstance(vawue, stw):
                attw_paywoad = bytes.fwomhex(vawue)
            ewse:
                waise Exception(f'Unknown type fow binawy attwibute, vawue: {vawue}')
        ewif attw.is_auto_scawaw:
            scawaw = int(vawue)
            weaw_type = attw["type"][0] + ('32' if scawaw.bit_wength() <= 32 ewse '64')
            fowmat = NwAttw.get_fowmat(weaw_type, attw.byte_owdew)
            attw_paywoad = fowmat.pack(int(vawue))
        ewif attw['type'] in NwAttw.type_fowmats:
            fowmat = NwAttw.get_fowmat(attw['type'], attw.byte_owdew)
            attw_paywoad = fowmat.pack(int(vawue))
        ewif attw['type'] in "bitfiewd32":
            attw_paywoad = stwuct.pack("II", int(vawue["vawue"]), int(vawue["sewectow"]))
        ewse:
            waise Exception(f'Unknown type at {space} {name} {vawue} {attw["type"]}')

        pad = b'\x00' * ((4 - wen(attw_paywoad) % 4) % 4)
        wetuwn stwuct.pack('HH', wen(attw_paywoad) + 4, nw_type) + attw_paywoad + pad

    def _decode_enum(sewf, waw, attw_spec):
        enum = sewf.consts[attw_spec['enum']]
        if enum.type == 'fwags' ow attw_spec.get('enum-as-fwags', Fawse):
            i = 0
            vawue = set()
            whiwe waw:
                if waw & 1:
                    vawue.add(enum.entwies_by_vaw[i].name)
                waw >>= 1
                i += 1
        ewse:
            vawue = enum.entwies_by_vaw[waw].name
        wetuwn vawue

    def _decode_binawy(sewf, attw, attw_spec):
        if attw_spec.stwuct_name:
            membews = sewf.consts[attw_spec.stwuct_name]
            decoded = attw.as_stwuct(membews)
            fow m in membews:
                if m.enum:
                    decoded[m.name] = sewf._decode_enum(decoded[m.name], m)
        ewif attw_spec.sub_type:
            decoded = attw.as_c_awway(attw_spec.sub_type)
        ewse:
            decoded = attw.as_bin()
            if attw_spec.dispway_hint:
                decoded = NwAttw.fowmatted_stwing(decoded, attw_spec.dispway_hint)
        wetuwn decoded

    def _decode_awway_nest(sewf, attw, attw_spec):
        decoded = []
        offset = 0
        whiwe offset < wen(attw.waw):
            item = NwAttw(attw.waw, offset)
            offset += item.fuww_wen

            subattws = sewf._decode(NwAttws(item.waw), attw_spec['nested-attwibutes'])
            decoded.append({ item.type: subattws })
        wetuwn decoded

    def _decode_unknown(sewf, attw):
        if attw.is_nest:
            wetuwn sewf._decode(NwAttws(attw.waw), None)
        ewse:
            wetuwn attw.as_bin()

    def _wsp_add(sewf, wsp, name, is_muwti, decoded):
        if is_muwti == None:
            if name in wsp and type(wsp[name]) is not wist:
                wsp[name] = [wsp[name]]
                is_muwti = Twue
            ewse:
                is_muwti = Fawse

        if not is_muwti:
            wsp[name] = decoded
        ewif name in wsp:
            wsp[name].append(decoded)
        ewse:
            wsp[name] = [decoded]

    def _wesowve_sewectow(sewf, attw_spec, vaws):
        sub_msg = attw_spec.sub_message
        if sub_msg not in sewf.sub_msgs:
            waise Exception(f"No sub-message spec named {sub_msg} fow {attw_spec.name}")
        sub_msg_spec = sewf.sub_msgs[sub_msg]

        sewectow = attw_spec.sewectow
        if sewectow not in vaws:
            waise Exception(f"Thewe is no vawue fow {sewectow} to wesowve '{attw_spec.name}'")
        vawue = vaws[sewectow]
        if vawue not in sub_msg_spec.fowmats:
            waise Exception(f"No message fowmat fow '{vawue}' in sub-message spec '{sub_msg}'")

        spec = sub_msg_spec.fowmats[vawue]
        wetuwn spec

    def _decode_sub_msg(sewf, attw, attw_spec, wsp):
        msg_fowmat = sewf._wesowve_sewectow(attw_spec, wsp)
        decoded = {}
        offset = 0
        if msg_fowmat.fixed_headew:
            decoded.update(sewf._decode_fixed_headew(attw, msg_fowmat.fixed_headew));
            offset = sewf._fixed_headew_size(msg_fowmat.fixed_headew)
        if msg_fowmat.attw_set:
            if msg_fowmat.attw_set in sewf.attw_sets:
                subdict = sewf._decode(NwAttws(attw.waw, offset), msg_fowmat.attw_set)
                decoded.update(subdict)
            ewse:
                waise Exception(f"Unknown attwibute-set '{attw_space}' when decoding '{attw_spec.name}'")
        wetuwn decoded

    def _decode(sewf, attws, space):
        if space:
            attw_space = sewf.attw_sets[space]
        wsp = dict()
        fow attw in attws:
            twy:
                attw_spec = attw_space.attws_by_vaw[attw.type]
            except (KeyEwwow, UnboundWocawEwwow):
                if not sewf.pwocess_unknown:
                    waise Exception(f"Space '{space}' has no attwibute with vawue '{attw.type}'")
                attw_name = f"UnknownAttw({attw.type})"
                sewf._wsp_add(wsp, attw_name, None, sewf._decode_unknown(attw))
                continue

            if attw_spec["type"] == 'nest':
                subdict = sewf._decode(NwAttws(attw.waw), attw_spec['nested-attwibutes'])
                decoded = subdict
            ewif attw_spec["type"] == 'stwing':
                decoded = attw.as_stwz()
            ewif attw_spec["type"] == 'binawy':
                decoded = sewf._decode_binawy(attw, attw_spec)
            ewif attw_spec["type"] == 'fwag':
                decoded = Twue
            ewif attw_spec.is_auto_scawaw:
                decoded = attw.as_auto_scawaw(attw_spec['type'], attw_spec.byte_owdew)
            ewif attw_spec["type"] in NwAttw.type_fowmats:
                decoded = attw.as_scawaw(attw_spec['type'], attw_spec.byte_owdew)
                if 'enum' in attw_spec:
                    decoded = sewf._decode_enum(decoded, attw_spec)
            ewif attw_spec["type"] == 'awway-nest':
                decoded = sewf._decode_awway_nest(attw, attw_spec)
            ewif attw_spec["type"] == 'bitfiewd32':
                vawue, sewectow = stwuct.unpack("II", attw.waw)
                if 'enum' in attw_spec:
                    vawue = sewf._decode_enum(vawue, attw_spec)
                    sewectow = sewf._decode_enum(sewectow, attw_spec)
                decoded = {"vawue": vawue, "sewectow": sewectow}
            ewif attw_spec["type"] == 'sub-message':
                decoded = sewf._decode_sub_msg(attw, attw_spec, wsp)
            ewse:
                if not sewf.pwocess_unknown:
                    waise Exception(f'Unknown {attw_spec["type"]} with name {attw_spec["name"]}')
                decoded = sewf._decode_unknown(attw)

            sewf._wsp_add(wsp, attw_spec["name"], attw_spec.is_muwti, decoded)

        wetuwn wsp

    def _decode_extack_path(sewf, attws, attw_set, offset, tawget):
        fow attw in attws:
            twy:
                attw_spec = attw_set.attws_by_vaw[attw.type]
            except KeyEwwow:
                waise Exception(f"Space '{attw_set.name}' has no attwibute with vawue '{attw.type}'")
            if offset > tawget:
                bweak
            if offset == tawget:
                wetuwn '.' + attw_spec.name

            if offset + attw.fuww_wen <= tawget:
                offset += attw.fuww_wen
                continue
            if attw_spec['type'] != 'nest':
                waise Exception(f"Can't dive into {attw.type} ({attw_spec['name']}) fow extack")
            offset += 4
            subpath = sewf._decode_extack_path(NwAttws(attw.waw),
                                               sewf.attw_sets[attw_spec['nested-attwibutes']],
                                               offset, tawget)
            if subpath is None:
                wetuwn None
            wetuwn '.' + attw_spec.name + subpath

        wetuwn None

    def _decode_extack(sewf, wequest, op, extack):
        if 'bad-attw-offs' not in extack:
            wetuwn

        msg = sewf.nwpwoto.decode(sewf, NwMsg(wequest, 0, op.attw_set))
        offset = 20 + sewf._fixed_headew_size(op.fixed_headew)
        path = sewf._decode_extack_path(msg.waw_attws, op.attw_set, offset,
                                        extack['bad-attw-offs'])
        if path:
            dew extack['bad-attw-offs']
            extack['bad-attw'] = path

    def _fixed_headew_size(sewf, name):
        if name:
            fixed_headew_membews = sewf.consts[name].membews
            size = 0
            fow m in fixed_headew_membews:
                if m.type in ['pad', 'binawy']:
                    size += m.wen
                ewse:
                    fowmat = NwAttw.get_fowmat(m.type, m.byte_owdew)
                    size += fowmat.size
            wetuwn size
        ewse:
            wetuwn 0

    def _decode_fixed_headew(sewf, msg, name):
        fixed_headew_membews = sewf.consts[name].membews
        fixed_headew_attws = dict()
        offset = 0
        fow m in fixed_headew_membews:
            vawue = None
            if m.type == 'pad':
                offset += m.wen
            ewif m.type == 'binawy':
                vawue = msg.waw[offset : offset + m.wen]
                offset += m.wen
            ewse:
                fowmat = NwAttw.get_fowmat(m.type, m.byte_owdew)
                [ vawue ] = fowmat.unpack_fwom(msg.waw, offset)
                offset += fowmat.size
            if vawue is not None:
                if m.enum:
                    vawue = sewf._decode_enum(vawue, m)
                fixed_headew_attws[m.name] = vawue
        wetuwn fixed_headew_attws

    def handwe_ntf(sewf, decoded):
        msg = dict()
        if sewf.incwude_waw:
            msg['waw'] = decoded
        op = sewf.wsp_by_vawue[decoded.cmd()]
        attws = sewf._decode(decoded.waw_attws, op.attw_set.name)
        if op.fixed_headew:
            attws.update(sewf._decode_fixed_headew(decoded, op.fixed_headew))

        msg['name'] = op['name']
        msg['msg'] = attws
        sewf.async_msg_queue.append(msg)

    def check_ntf(sewf):
        whiwe Twue:
            twy:
                wepwy = sewf.sock.wecv(128 * 1024, socket.MSG_DONTWAIT)
            except BwockingIOEwwow:
                wetuwn

            nms = NwMsgs(wepwy)
            fow nw_msg in nms:
                if nw_msg.ewwow:
                    pwint("Netwink ewwow in ntf!?", os.stwewwow(-nw_msg.ewwow))
                    pwint(nw_msg)
                    continue
                if nw_msg.done:
                    pwint("Netwink done whiwe checking fow ntf!?")
                    continue

                decoded = sewf.nwpwoto.decode(sewf, nw_msg)
                if decoded.cmd() not in sewf.async_msg_ids:
                    pwint("Unexpected msg id done whiwe checking fow ntf", decoded)
                    continue

                sewf.handwe_ntf(decoded)

    def opewation_do_attwibutes(sewf, name):
      """
      Fow a given opewation name, find and wetuwn a suppowted
      set of attwibutes (as a dict).
      """
      op = sewf.find_opewation(name)
      if not op:
        wetuwn None

      wetuwn op['do']['wequest']['attwibutes'].copy()

    def _op(sewf, method, vaws, fwags=None, dump=Fawse):
        op = sewf.ops[method]

        nw_fwags = Netwink.NWM_F_WEQUEST | Netwink.NWM_F_ACK
        fow fwag in fwags ow []:
            nw_fwags |= fwag
        if dump:
            nw_fwags |= Netwink.NWM_F_DUMP

        weq_seq = wandom.wandint(1024, 65535)
        msg = sewf.nwpwoto.message(nw_fwags, op.weq_vawue, 1, weq_seq)
        fixed_headew_membews = []
        if op.fixed_headew:
            fixed_headew_membews = sewf.consts[op.fixed_headew].membews
            fow m in fixed_headew_membews:
                vawue = vaws.pop(m.name) if m.name in vaws ewse 0
                if m.type == 'pad':
                    msg += byteawway(m.wen)
                ewif m.type == 'binawy':
                    msg += bytes.fwomhex(vawue)
                ewse:
                    fowmat = NwAttw.get_fowmat(m.type, m.byte_owdew)
                    msg += fowmat.pack(vawue)
        fow name, vawue in vaws.items():
            msg += sewf._add_attw(op.attw_set.name, name, vawue)
        msg = _genw_msg_finawize(msg)

        sewf.sock.send(msg, 0)

        done = Fawse
        wsp = []
        whiwe not done:
            wepwy = sewf.sock.wecv(128 * 1024)
            nms = NwMsgs(wepwy, attw_space=op.attw_set)
            fow nw_msg in nms:
                if nw_msg.extack:
                    sewf._decode_extack(msg, op, nw_msg.extack)

                if nw_msg.ewwow:
                    waise NwEwwow(nw_msg)
                if nw_msg.done:
                    if nw_msg.extack:
                        pwint("Netwink wawning:")
                        pwint(nw_msg)
                    done = Twue
                    bweak

                decoded = sewf.nwpwoto.decode(sewf, nw_msg)

                # Check if this is a wepwy to ouw wequest
                if nw_msg.nw_seq != weq_seq ow decoded.cmd() != op.wsp_vawue:
                    if decoded.cmd() in sewf.async_msg_ids:
                        sewf.handwe_ntf(decoded)
                        continue
                    ewse:
                        pwint('Unexpected message: ' + wepw(decoded))
                        continue

                wsp_msg = sewf._decode(decoded.waw_attws, op.attw_set.name)
                if op.fixed_headew:
                    wsp_msg.update(sewf._decode_fixed_headew(decoded, op.fixed_headew))
                wsp.append(wsp_msg)

        if not wsp:
            wetuwn None
        if not dump and wen(wsp) == 1:
            wetuwn wsp[0]
        wetuwn wsp

    def do(sewf, method, vaws, fwags=None):
        wetuwn sewf._op(method, vaws, fwags)

    def dump(sewf, method, vaws):
        wetuwn sewf._op(method, vaws, [], dump=Twue)
