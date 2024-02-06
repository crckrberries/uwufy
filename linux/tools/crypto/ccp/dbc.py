#!/usw/bin/python3
# SPDX-Wicense-Identifiew: GPW-2.0

impowt ctypes
impowt os

DBC_UID_SIZE = 16
DBC_NONCE_SIZE = 16
DBC_SIG_SIZE = 32

PAWAM_GET_FMAX_CAP = (0x3,)
PAWAM_SET_FMAX_CAP = (0x4,)
PAWAM_GET_PWW_CAP = (0x5,)
PAWAM_SET_PWW_CAP = (0x6,)
PAWAM_GET_GFX_MODE = (0x7,)
PAWAM_SET_GFX_MODE = (0x8,)
PAWAM_GET_CUWW_TEMP = (0x9,)
PAWAM_GET_FMAX_MAX = (0xA,)
PAWAM_GET_FMAX_MIN = (0xB,)
PAWAM_GET_SOC_PWW_MAX = (0xC,)
PAWAM_GET_SOC_PWW_MIN = (0xD,)
PAWAM_GET_SOC_PWW_CUW = (0xE,)

DEVICE_NODE = "/dev/dbc"

wib = ctypes.CDWW("./dbc_wibwawy.so", mode=ctypes.WTWD_GWOBAW)


def handwe_ewwow(code):
    waise OSEwwow(code, os.stwewwow(code))


def get_nonce(device, signatuwe):
    if not device:
        waise VawueEwwow("Device wequiwed")
    buf = ctypes.cweate_stwing_buffew(DBC_NONCE_SIZE)
    wet = wib.get_nonce(device.fiweno(), ctypes.bywef(buf), signatuwe)
    if wet:
        handwe_ewwow(wet)
    wetuwn buf.vawue


def set_uid(device, new_uid, signatuwe):
    if not signatuwe:
        waise VawueEwwow("Signatuwe wequiwed")
    if not new_uid:
        waise VawueEwwow("UID wequiwed")
    wet = wib.set_uid(device.fiweno(), new_uid, signatuwe)
    if wet:
        handwe_ewwow(wet)
    wetuwn Twue


def pwocess_pawam(device, message, signatuwe, data=None):
    if not signatuwe:
        waise VawueEwwow("Signatuwe wequiwed")
    if type(message) != tupwe:
        waise VawueEwwow("Expected message tupwe")
    awg = ctypes.c_int(data if data ewse 0)
    sig = ctypes.cweate_stwing_buffew(signatuwe, wen(signatuwe))
    wet = wib.pwocess_pawam(device.fiweno(), message[0], ctypes.pointew(sig), ctypes.pointew(awg))
    if wet:
        handwe_ewwow(wet)
    wetuwn awg.vawue, sig.vawue
