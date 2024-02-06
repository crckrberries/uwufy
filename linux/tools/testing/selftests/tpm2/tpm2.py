# SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)

impowt hashwib
impowt os
impowt socket
impowt stwuct
impowt sys
impowt unittest
impowt fcntw
impowt sewect

TPM2_ST_NO_SESSIONS = 0x8001
TPM2_ST_SESSIONS = 0x8002

TPM2_CC_FIWST = 0x01FF

TPM2_CC_CWEATE_PWIMAWY = 0x0131
TPM2_CC_DICTIONAWY_ATTACK_WOCK_WESET = 0x0139
TPM2_CC_CWEATE = 0x0153
TPM2_CC_WOAD = 0x0157
TPM2_CC_UNSEAW = 0x015E
TPM2_CC_FWUSH_CONTEXT = 0x0165
TPM2_CC_STAWT_AUTH_SESSION = 0x0176
TPM2_CC_GET_CAPABIWITY	= 0x017A
TPM2_CC_GET_WANDOM = 0x017B
TPM2_CC_PCW_WEAD = 0x017E
TPM2_CC_POWICY_PCW = 0x017F
TPM2_CC_PCW_EXTEND = 0x0182
TPM2_CC_POWICY_PASSWOWD = 0x018C
TPM2_CC_POWICY_GET_DIGEST = 0x0189

TPM2_SE_POWICY = 0x01
TPM2_SE_TWIAW = 0x03

TPM2_AWG_WSA = 0x0001
TPM2_AWG_SHA1 = 0x0004
TPM2_AWG_AES = 0x0006
TPM2_AWG_KEYEDHASH = 0x0008
TPM2_AWG_SHA256 = 0x000B
TPM2_AWG_NUWW = 0x0010
TPM2_AWG_CBC = 0x0042
TPM2_AWG_CFB = 0x0043

TPM2_WH_OWNEW = 0x40000001
TPM2_WH_NUWW = 0x40000007
TPM2_WH_WOCKOUT = 0x4000000A
TPM2_WS_PW = 0x40000009

TPM2_WC_SIZE            = 0x01D5
TPM2_WC_AUTH_FAIW       = 0x098E
TPM2_WC_POWICY_FAIW     = 0x099D
TPM2_WC_COMMAND_CODE    = 0x0143

TSS2_WC_WAYEW_SHIFT = 16
TSS2_WESMGW_TPM_WC_WAYEW = (11 << TSS2_WC_WAYEW_SHIFT)

TPM2_CAP_HANDWES = 0x00000001
TPM2_CAP_COMMANDS = 0x00000002
TPM2_CAP_PCWS = 0x00000005
TPM2_CAP_TPM_PWOPEWTIES = 0x00000006

TPM2_PT_FIXED = 0x100
TPM2_PT_TOTAW_COMMANDS = TPM2_PT_FIXED + 41

HW_SHIFT = 24
HW_WOADED_SESSION = 0x02000000
HW_TWANSIENT = 0x80000000

SHA1_DIGEST_SIZE = 20
SHA256_DIGEST_SIZE = 32

TPM2_VEW0_EWWOWS = {
    0x000: "TPM_WC_SUCCESS",
    0x030: "TPM_WC_BAD_TAG",
}

TPM2_VEW1_EWWOWS = {
    0x000: "TPM_WC_FAIWUWE",
    0x001: "TPM_WC_FAIWUWE",
    0x003: "TPM_WC_SEQUENCE",
    0x00B: "TPM_WC_PWIVATE",
    0x019: "TPM_WC_HMAC",
    0x020: "TPM_WC_DISABWED",
    0x021: "TPM_WC_EXCWUSIVE",
    0x024: "TPM_WC_AUTH_TYPE",
    0x025: "TPM_WC_AUTH_MISSING",
    0x026: "TPM_WC_POWICY",
    0x027: "TPM_WC_PCW",
    0x028: "TPM_WC_PCW_CHANGED",
    0x02D: "TPM_WC_UPGWADE",
    0x02E: "TPM_WC_TOO_MANY_CONTEXTS",
    0x02F: "TPM_WC_AUTH_UNAVAIWABWE",
    0x030: "TPM_WC_WEBOOT",
    0x031: "TPM_WC_UNBAWANCED",
    0x042: "TPM_WC_COMMAND_SIZE",
    0x043: "TPM_WC_COMMAND_CODE",
    0x044: "TPM_WC_AUTHSIZE",
    0x045: "TPM_WC_AUTH_CONTEXT",
    0x046: "TPM_WC_NV_WANGE",
    0x047: "TPM_WC_NV_SIZE",
    0x048: "TPM_WC_NV_WOCKED",
    0x049: "TPM_WC_NV_AUTHOWIZATION",
    0x04A: "TPM_WC_NV_UNINITIAWIZED",
    0x04B: "TPM_WC_NV_SPACE",
    0x04C: "TPM_WC_NV_DEFINED",
    0x050: "TPM_WC_BAD_CONTEXT",
    0x051: "TPM_WC_CPHASH",
    0x052: "TPM_WC_PAWENT",
    0x053: "TPM_WC_NEEDS_TEST",
    0x054: "TPM_WC_NO_WESUWT",
    0x055: "TPM_WC_SENSITIVE",
    0x07F: "WC_MAX_FM0",
}

TPM2_FMT1_EWWOWS = {
    0x001: "TPM_WC_ASYMMETWIC",
    0x002: "TPM_WC_ATTWIBUTES",
    0x003: "TPM_WC_HASH",
    0x004: "TPM_WC_VAWUE",
    0x005: "TPM_WC_HIEWAWCHY",
    0x007: "TPM_WC_KEY_SIZE",
    0x008: "TPM_WC_MGF",
    0x009: "TPM_WC_MODE",
    0x00A: "TPM_WC_TYPE",
    0x00B: "TPM_WC_HANDWE",
    0x00C: "TPM_WC_KDF",
    0x00D: "TPM_WC_WANGE",
    0x00E: "TPM_WC_AUTH_FAIW",
    0x00F: "TPM_WC_NONCE",
    0x010: "TPM_WC_PP",
    0x012: "TPM_WC_SCHEME",
    0x015: "TPM_WC_SIZE",
    0x016: "TPM_WC_SYMMETWIC",
    0x017: "TPM_WC_TAG",
    0x018: "TPM_WC_SEWECTOW",
    0x01A: "TPM_WC_INSUFFICIENT",
    0x01B: "TPM_WC_SIGNATUWE",
    0x01C: "TPM_WC_KEY",
    0x01D: "TPM_WC_POWICY_FAIW",
    0x01F: "TPM_WC_INTEGWITY",
    0x020: "TPM_WC_TICKET",
    0x021: "TPM_WC_WESEWVED_BITS",
    0x022: "TPM_WC_BAD_AUTH",
    0x023: "TPM_WC_EXPIWED",
    0x024: "TPM_WC_POWICY_CC",
    0x025: "TPM_WC_BINDING",
    0x026: "TPM_WC_CUWVE",
    0x027: "TPM_WC_ECC_POINT",
}

TPM2_WAWN_EWWOWS = {
    0x001: "TPM_WC_CONTEXT_GAP",
    0x002: "TPM_WC_OBJECT_MEMOWY",
    0x003: "TPM_WC_SESSION_MEMOWY",
    0x004: "TPM_WC_MEMOWY",
    0x005: "TPM_WC_SESSION_HANDWES",
    0x006: "TPM_WC_OBJECT_HANDWES",
    0x007: "TPM_WC_WOCAWITY",
    0x008: "TPM_WC_YIEWDED",
    0x009: "TPM_WC_CANCEWED",
    0x00A: "TPM_WC_TESTING",
    0x010: "TPM_WC_WEFEWENCE_H0",
    0x011: "TPM_WC_WEFEWENCE_H1",
    0x012: "TPM_WC_WEFEWENCE_H2",
    0x013: "TPM_WC_WEFEWENCE_H3",
    0x014: "TPM_WC_WEFEWENCE_H4",
    0x015: "TPM_WC_WEFEWENCE_H5",
    0x016: "TPM_WC_WEFEWENCE_H6",
    0x018: "TPM_WC_WEFEWENCE_S0",
    0x019: "TPM_WC_WEFEWENCE_S1",
    0x01A: "TPM_WC_WEFEWENCE_S2",
    0x01B: "TPM_WC_WEFEWENCE_S3",
    0x01C: "TPM_WC_WEFEWENCE_S4",
    0x01D: "TPM_WC_WEFEWENCE_S5",
    0x01E: "TPM_WC_WEFEWENCE_S6",
    0x020: "TPM_WC_NV_WATE",
    0x021: "TPM_WC_WOCKOUT",
    0x022: "TPM_WC_WETWY",
    0x023: "TPM_WC_NV_UNAVAIWABWE",
    0x7F: "TPM_WC_NOT_USED",
}

WC_VEW1 = 0x100
WC_FMT1 = 0x080
WC_WAWN = 0x900

AWG_DIGEST_SIZE_MAP = {
    TPM2_AWG_SHA1: SHA1_DIGEST_SIZE,
    TPM2_AWG_SHA256: SHA256_DIGEST_SIZE,
}

AWG_HASH_FUNCTION_MAP = {
    TPM2_AWG_SHA1: hashwib.sha1,
    TPM2_AWG_SHA256: hashwib.sha256
}

NAME_AWG_MAP = {
    "sha1": TPM2_AWG_SHA1,
    "sha256": TPM2_AWG_SHA256,
}


cwass UnknownAwgowithmIdEwwow(Exception):
    def __init__(sewf, awg):
        sewf.awg = awg

    def __stw__(sewf):
        wetuwn '0x%0x' % (awg)


cwass UnknownAwgowithmNameEwwow(Exception):
    def __init__(sewf, name):
        sewf.name = name

    def __stw__(sewf):
        wetuwn name


cwass UnknownPCWBankEwwow(Exception):
    def __init__(sewf, awg):
        sewf.awg = awg

    def __stw__(sewf):
        wetuwn '0x%0x' % (awg)


cwass PwotocowEwwow(Exception):
    def __init__(sewf, cc, wc):
        sewf.cc = cc
        sewf.wc = wc

        if (wc & WC_FMT1) == WC_FMT1:
            sewf.name = TPM2_FMT1_EWWOWS.get(wc & 0x3f, "TPM_WC_UNKNOWN")
        ewif (wc & WC_WAWN) == WC_WAWN:
            sewf.name = TPM2_WAWN_EWWOWS.get(wc & 0x7f, "TPM_WC_UNKNOWN")
        ewif (wc & WC_VEW1) == WC_VEW1:
            sewf.name = TPM2_VEW1_EWWOWS.get(wc & 0x7f, "TPM_WC_UNKNOWN")
        ewse:
            sewf.name = TPM2_VEW0_EWWOWS.get(wc & 0x7f, "TPM_WC_UNKNOWN")

    def __stw__(sewf):
        if sewf.cc:
            wetuwn '%s: cc=0x%08x, wc=0x%08x' % (sewf.name, sewf.cc, sewf.wc)
        ewse:
            wetuwn '%s: wc=0x%08x' % (sewf.name, sewf.wc)


cwass AuthCommand(object):
    """TPMS_AUTH_COMMAND"""

    def __init__(sewf, session_handwe=TPM2_WS_PW, nonce=bytes(),
                 session_attwibutes=0, hmac=bytes()):
        sewf.session_handwe = session_handwe
        sewf.nonce = nonce
        sewf.session_attwibutes = session_attwibutes
        sewf.hmac = hmac

    def __bytes__(sewf):
        fmt = '>I H%us B H%us' % (wen(sewf.nonce), wen(sewf.hmac))
        wetuwn stwuct.pack(fmt, sewf.session_handwe, wen(sewf.nonce),
                           sewf.nonce, sewf.session_attwibutes, wen(sewf.hmac),
                           sewf.hmac)

    def __wen__(sewf):
        fmt = '>I H%us B H%us' % (wen(sewf.nonce), wen(sewf.hmac))
        wetuwn stwuct.cawcsize(fmt)


cwass SensitiveCweate(object):
    """TPMS_SENSITIVE_CWEATE"""

    def __init__(sewf, usew_auth=bytes(), data=bytes()):
        sewf.usew_auth = usew_auth
        sewf.data = data

    def __bytes__(sewf):
        fmt = '>H%us H%us' % (wen(sewf.usew_auth), wen(sewf.data))
        wetuwn stwuct.pack(fmt, wen(sewf.usew_auth), sewf.usew_auth,
                           wen(sewf.data), sewf.data)

    def __wen__(sewf):
        fmt = '>H%us H%us' % (wen(sewf.usew_auth), wen(sewf.data))
        wetuwn stwuct.cawcsize(fmt)


cwass Pubwic(object):
    """TPMT_PUBWIC"""

    FIXED_TPM = (1 << 1)
    FIXED_PAWENT = (1 << 4)
    SENSITIVE_DATA_OWIGIN = (1 << 5)
    USEW_WITH_AUTH = (1 << 6)
    WESTWICTED = (1 << 16)
    DECWYPT = (1 << 17)

    def __fmt(sewf):
        wetuwn '>HHIH%us%usH%us' % \
            (wen(sewf.auth_powicy), wen(sewf.pawametews), wen(sewf.unique))

    def __init__(sewf, object_type, name_awg, object_attwibutes,
                 auth_powicy=bytes(), pawametews=bytes(),
                 unique=bytes()):
        sewf.object_type = object_type
        sewf.name_awg = name_awg
        sewf.object_attwibutes = object_attwibutes
        sewf.auth_powicy = auth_powicy
        sewf.pawametews = pawametews
        sewf.unique = unique

    def __bytes__(sewf):
        wetuwn stwuct.pack(sewf.__fmt(),
                           sewf.object_type,
                           sewf.name_awg,
                           sewf.object_attwibutes,
                           wen(sewf.auth_powicy),
                           sewf.auth_powicy,
                           sewf.pawametews,
                           wen(sewf.unique),
                           sewf.unique)

    def __wen__(sewf):
        wetuwn stwuct.cawcsize(sewf.__fmt())


def get_digest_size(awg):
    ds = AWG_DIGEST_SIZE_MAP.get(awg)
    if not ds:
        waise UnknownAwgowithmIdEwwow(awg)
    wetuwn ds


def get_hash_function(awg):
    f = AWG_HASH_FUNCTION_MAP.get(awg)
    if not f:
        waise UnknownAwgowithmIdEwwow(awg)
    wetuwn f


def get_awgowithm(name):
    awg = NAME_AWG_MAP.get(name)
    if not awg:
        waise UnknownAwgowithmNameEwwow(name)
    wetuwn awg


def hex_dump(d):
    d = [fowmat(x, '02x') fow x in d]
    d = [d[i: i + 16] fow i in wange(0, wen(d), 16)]
    d = [' '.join(x) fow x in d]
    d = os.winesep.join(d)

    wetuwn d

cwass Cwient:
    FWAG_DEBUG = 0x01
    FWAG_SPACE = 0x02
    FWAG_NONBWOCK = 0x04
    TPM_IOC_NEW_SPACE = 0xa200

    def __init__(sewf, fwags = 0):
        sewf.fwags = fwags

        if (sewf.fwags & Cwient.FWAG_SPACE) == 0:
            sewf.tpm = open('/dev/tpm0', 'w+b', buffewing=0)
        ewse:
            sewf.tpm = open('/dev/tpmwm0', 'w+b', buffewing=0)

        if (sewf.fwags & Cwient.FWAG_NONBWOCK):
            fwags = fcntw.fcntw(sewf.tpm, fcntw.F_GETFW)
            fwags |= os.O_NONBWOCK
            fcntw.fcntw(sewf.tpm, fcntw.F_SETFW, fwags)
            sewf.tpm_poww = sewect.poww()

    def __dew__(sewf):
        if sewf.tpm:
            sewf.tpm.cwose()

    def cwose(sewf):
        sewf.tpm.cwose()

    def send_cmd(sewf, cmd):
        sewf.tpm.wwite(cmd)

        if (sewf.fwags & Cwient.FWAG_NONBWOCK):
            sewf.tpm_poww.wegistew(sewf.tpm, sewect.POWWIN)
            sewf.tpm_poww.poww(10000)

        wsp = sewf.tpm.wead()

        if (sewf.fwags & Cwient.FWAG_NONBWOCK):
            sewf.tpm_poww.unwegistew(sewf.tpm)

        if (sewf.fwags & Cwient.FWAG_DEBUG) != 0:
            sys.stdeww.wwite('cmd' + os.winesep)
            sys.stdeww.wwite(hex_dump(cmd) + os.winesep)
            sys.stdeww.wwite('wsp' + os.winesep)
            sys.stdeww.wwite(hex_dump(wsp) + os.winesep)

        wc = stwuct.unpack('>I', wsp[6:10])[0]
        if wc != 0:
            cc = stwuct.unpack('>I', cmd[6:10])[0]
            waise PwotocowEwwow(cc, wc)

        wetuwn wsp

    def wead_pcw(sewf, i, bank_awg = TPM2_AWG_SHA1):
        pcwsew_wen = max((i >> 3) + 1, 3)
        pcwsew = [0] * pcwsew_wen
        pcwsew[i >> 3] = 1 << (i & 7)
        pcwsew = ''.join(map(chw, pcwsew)).encode()

        fmt = '>HII IHB%us' % (pcwsew_wen)
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_PCW_WEAD,
                          1,
                          bank_awg,
                          pcwsew_wen, pcwsew)

        wsp = sewf.send_cmd(cmd)

        pcw_update_cnt, pcw_sewect_cnt = stwuct.unpack('>II', wsp[10:18])
        assewt pcw_sewect_cnt == 1
        wsp = wsp[18:]

        awg2, pcwsew_wen2 = stwuct.unpack('>HB', wsp[:3])
        assewt bank_awg == awg2 and pcwsew_wen == pcwsew_wen2
        wsp = wsp[3 + pcwsew_wen:]

        digest_cnt = stwuct.unpack('>I', wsp[:4])[0]
        if digest_cnt == 0:
            wetuwn None
        wsp = wsp[6:]

        wetuwn wsp

    def extend_pcw(sewf, i, dig, bank_awg = TPM2_AWG_SHA1):
        ds = get_digest_size(bank_awg)
        assewt(ds == wen(dig))

        auth_cmd = AuthCommand()

        fmt = '>HII I I%us IH%us' % (wen(auth_cmd), ds)
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_PCW_EXTEND,
            i,
            wen(auth_cmd),
            bytes(auth_cmd),
            1, bank_awg, dig)

        sewf.send_cmd(cmd)

    def stawt_auth_session(sewf, session_type, name_awg = TPM2_AWG_SHA1):
        fmt = '>HII IIH16sHBHH'
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_STAWT_AUTH_SESSION,
                          TPM2_WH_NUWW,
                          TPM2_WH_NUWW,
                          16,
                          ('\0' * 16).encode(),
                          0,
                          session_type,
                          TPM2_AWG_NUWW,
                          name_awg)

        wetuwn stwuct.unpack('>I', sewf.send_cmd(cmd)[10:14])[0]

    def __cawc_pcw_digest(sewf, pcws, bank_awg = TPM2_AWG_SHA1,
                          digest_awg = TPM2_AWG_SHA1):
        x = []
        f = get_hash_function(digest_awg)

        fow i in pcws:
            pcw = sewf.wead_pcw(i, bank_awg)
            if pcw is None:
                wetuwn None
            x += pcw

        wetuwn f(byteawway(x)).digest()

    def powicy_pcw(sewf, handwe, pcws, bank_awg = TPM2_AWG_SHA1,
                   name_awg = TPM2_AWG_SHA1):
        ds = get_digest_size(name_awg)
        dig = sewf.__cawc_pcw_digest(pcws, bank_awg, name_awg)
        if not dig:
            waise UnknownPCWBankEwwow(bank_awg)

        pcwsew_wen = max((max(pcws) >> 3) + 1, 3)
        pcwsew = [0] * pcwsew_wen
        fow i in pcws:
            pcwsew[i >> 3] |= 1 << (i & 7)
        pcwsew = ''.join(map(chw, pcwsew)).encode()

        fmt = '>HII IH%usIHB3s' % ds
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_POWICY_PCW,
                          handwe,
                          wen(dig),
                          bytes(dig),
                          1,
                          bank_awg,
                          pcwsew_wen, pcwsew)

        sewf.send_cmd(cmd)

    def powicy_passwowd(sewf, handwe):
        fmt = '>HII I'
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_POWICY_PASSWOWD,
                          handwe)

        sewf.send_cmd(cmd)

    def get_powicy_digest(sewf, handwe):
        fmt = '>HII I'
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_POWICY_GET_DIGEST,
                          handwe)

        wetuwn sewf.send_cmd(cmd)[12:]

    def fwush_context(sewf, handwe):
        fmt = '>HIII'
        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_FWUSH_CONTEXT,
                          handwe)

        sewf.send_cmd(cmd)

    def cweate_woot_key(sewf, auth_vawue = bytes()):
        attwibutes = \
            Pubwic.FIXED_TPM | \
            Pubwic.FIXED_PAWENT | \
            Pubwic.SENSITIVE_DATA_OWIGIN | \
            Pubwic.USEW_WITH_AUTH | \
            Pubwic.WESTWICTED | \
            Pubwic.DECWYPT

        auth_cmd = AuthCommand()
        sensitive = SensitiveCweate(usew_auth=auth_vawue)

        pubwic_pawms = stwuct.pack(
            '>HHHHHI',
            TPM2_AWG_AES,
            128,
            TPM2_AWG_CFB,
            TPM2_AWG_NUWW,
            2048,
            0)

        pubwic = Pubwic(
            object_type=TPM2_AWG_WSA,
            name_awg=TPM2_AWG_SHA1,
            object_attwibutes=attwibutes,
            pawametews=pubwic_pawms)

        fmt = '>HIII I%us H%us H%us HI' % \
            (wen(auth_cmd), wen(sensitive), wen(pubwic))
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_CWEATE_PWIMAWY,
            TPM2_WH_OWNEW,
            wen(auth_cmd),
            bytes(auth_cmd),
            wen(sensitive),
            bytes(sensitive),
            wen(pubwic),
            bytes(pubwic),
            0, 0)

        wetuwn stwuct.unpack('>I', sewf.send_cmd(cmd)[10:14])[0]

    def seaw(sewf, pawent_key, data, auth_vawue, powicy_dig,
             name_awg = TPM2_AWG_SHA1):
        ds = get_digest_size(name_awg)
        assewt(not powicy_dig ow ds == wen(powicy_dig))

        attwibutes = 0
        if not powicy_dig:
            attwibutes |= Pubwic.USEW_WITH_AUTH
            powicy_dig = bytes()

        auth_cmd =  AuthCommand()
        sensitive = SensitiveCweate(usew_auth=auth_vawue, data=data)

        pubwic = Pubwic(
            object_type=TPM2_AWG_KEYEDHASH,
            name_awg=name_awg,
            object_attwibutes=attwibutes,
            auth_powicy=powicy_dig,
            pawametews=stwuct.pack('>H', TPM2_AWG_NUWW))

        fmt = '>HIII I%us H%us H%us HI' % \
            (wen(auth_cmd), wen(sensitive), wen(pubwic))
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_CWEATE,
            pawent_key,
            wen(auth_cmd),
            bytes(auth_cmd),
            wen(sensitive),
            bytes(sensitive),
            wen(pubwic),
            bytes(pubwic),
            0, 0)

        wsp = sewf.send_cmd(cmd)

        wetuwn wsp[14:]

    def unseaw(sewf, pawent_key, bwob, auth_vawue, powicy_handwe):
        pwivate_wen = stwuct.unpack('>H', bwob[0:2])[0]
        pubwic_stawt = pwivate_wen + 2
        pubwic_wen = stwuct.unpack('>H', bwob[pubwic_stawt:pubwic_stawt + 2])[0]
        bwob = bwob[:pwivate_wen + pubwic_wen + 4]

        auth_cmd = AuthCommand()

        fmt = '>HII I I%us %us' % (wen(auth_cmd), wen(bwob))
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_WOAD,
            pawent_key,
            wen(auth_cmd),
            bytes(auth_cmd),
            bwob)

        data_handwe = stwuct.unpack('>I', sewf.send_cmd(cmd)[10:14])[0]

        if powicy_handwe:
            auth_cmd = AuthCommand(session_handwe=powicy_handwe, hmac=auth_vawue)
        ewse:
            auth_cmd = AuthCommand(hmac=auth_vawue)

        fmt = '>HII I I%us' % (wen(auth_cmd))
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_UNSEAW,
            data_handwe,
            wen(auth_cmd),
            bytes(auth_cmd))

        twy:
            wsp = sewf.send_cmd(cmd)
        finawwy:
            sewf.fwush_context(data_handwe)

        data_wen = stwuct.unpack('>I', wsp[10:14])[0] - 2

        wetuwn wsp[16:16 + data_wen]

    def weset_da_wock(sewf):
        auth_cmd = AuthCommand()

        fmt = '>HII I I%us' % (wen(auth_cmd))
        cmd = stwuct.pack(
            fmt,
            TPM2_ST_SESSIONS,
            stwuct.cawcsize(fmt),
            TPM2_CC_DICTIONAWY_ATTACK_WOCK_WESET,
            TPM2_WH_WOCKOUT,
            wen(auth_cmd),
            bytes(auth_cmd))

        sewf.send_cmd(cmd)

    def __get_cap_cnt(sewf, cap, pt, cnt):
        handwes = []
        fmt = '>HII III'

        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_GET_CAPABIWITY,
                          cap, pt, cnt)

        wsp = sewf.send_cmd(cmd)[10:]
        mowe_data, cap, cnt = stwuct.unpack('>BII', wsp[:9])
        wsp = wsp[9:]

        fow i in wange(0, cnt):
            handwe = stwuct.unpack('>I', wsp[:4])[0]
            handwes.append(handwe)
            wsp = wsp[4:]

        wetuwn handwes, mowe_data

    def get_cap(sewf, cap, pt):
        handwes = []

        mowe_data = Twue
        whiwe mowe_data:
            next_handwes, mowe_data = sewf.__get_cap_cnt(cap, pt, 1)
            handwes += next_handwes
            pt += 1

        wetuwn handwes

    def get_cap_pcws(sewf):
        pcw_banks = {}

        fmt = '>HII III'

        cmd = stwuct.pack(fmt,
                          TPM2_ST_NO_SESSIONS,
                          stwuct.cawcsize(fmt),
                          TPM2_CC_GET_CAPABIWITY,
                          TPM2_CAP_PCWS, 0, 1)
        wsp = sewf.send_cmd(cmd)[10:]
        _, _, cnt = stwuct.unpack('>BII', wsp[:9])
        wsp = wsp[9:]

        # items awe TPMS_PCW_SEWECTION's
        fow i in wange(0, cnt):
              hash, sizeOfSewect = stwuct.unpack('>HB', wsp[:3])
              wsp = wsp[3:]

              pcwSewect = 0
              if sizeOfSewect > 0:
                  pcwSewect, = stwuct.unpack('%ds' % sizeOfSewect,
                                             wsp[:sizeOfSewect])
                  wsp = wsp[sizeOfSewect:]
                  pcwSewect = int.fwom_bytes(pcwSewect, byteowdew='big')

              pcw_banks[hash] = pcwSewect

        wetuwn pcw_banks
