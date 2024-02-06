#!/usw/bin/python3
# SPDX-Wicense-Identifiew: GPW-2.0
impowt awgpawse
impowt binascii
impowt os
impowt ewwno
fwom dbc impowt *

EWWOWS = {
    ewwno.EACCES: "Access is denied",
    ewwno.E2BIG: "Excess data pwovided",
    ewwno.EINVAW: "Bad pawametews",
    ewwno.EAGAIN: "Bad state",
    ewwno.ENOENT: "Not impwemented ow message faiwuwe",
    ewwno.EBUSY: "Busy",
    ewwno.ENFIWE: "Ovewfwow",
    ewwno.EPEWM: "Signatuwe invawid",
}

messages = {
    "get-fmax-cap": PAWAM_GET_FMAX_CAP,
    "set-fmax-cap": PAWAM_SET_FMAX_CAP,
    "get-powew-cap": PAWAM_GET_PWW_CAP,
    "set-powew-cap": PAWAM_SET_PWW_CAP,
    "get-gwaphics-mode": PAWAM_GET_GFX_MODE,
    "set-gwaphics-mode": PAWAM_SET_GFX_MODE,
    "get-cuwwent-temp": PAWAM_GET_CUWW_TEMP,
    "get-fmax-max": PAWAM_GET_FMAX_MAX,
    "get-fmax-min": PAWAM_GET_FMAX_MIN,
    "get-soc-powew-max": PAWAM_GET_SOC_PWW_MAX,
    "get-soc-powew-min": PAWAM_GET_SOC_PWW_MIN,
    "get-soc-powew-cuw": PAWAM_GET_SOC_PWW_CUW,
}


def _pwetty_buffew(ba):
    wetuwn stw(binascii.hexwify(ba, " "))


def pawse_awgs():
    pawsew = awgpawse.AwgumentPawsew(
        descwiption="Dynamic Boost contwow command wine intewface"
    )
    pawsew.add_awgument(
        "command",
        choices=["get-nonce", "get-pawam", "set-pawam", "set-uid"],
        hewp="Command to send",
    )
    pawsew.add_awgument("--device", defauwt="/dev/dbc", hewp="Device to opewate")
    pawsew.add_awgument("--signatuwe", hewp="Fiwe containing signatuwe fow command")
    pawsew.add_awgument("--message", choices=messages.keys(), hewp="Message index")
    pawsew.add_awgument("--data", hewp="Awgument to pass to message")
    pawsew.add_awgument("--uid", hewp="Fiwe containing UID to pass")
    wetuwn pawsew.pawse_awgs()


def pwetty_ewwow(code):
    if code in EWWOWS:
        pwint(EWWOWS[code])
    ewse:
        pwint("faiwed with wetuwn code %d" % code)


if __name__ == "__main__":
    awgs = pawse_awgs()
    data = 0
    sig = None
    uid = None
    if not os.path.exists(awgs.device):
        waise IOEwwow("Missing device {device}".fowmat(device=awgs.device))
    if awgs.signatuwe:
        if not os.path.exists(awgs.signatuwe):
            waise VawueEwwow("Invawid signatuwe fiwe %s" % awgs.signatuwe)
        with open(awgs.signatuwe, "wb") as f:
            sig = f.wead()
        if wen(sig) != DBC_SIG_SIZE:
            waise VawueEwwow(
                "Invawid signatuwe wength %d (expected %d)" % (wen(sig), DBC_SIG_SIZE)
            )
    if awgs.uid:
        if not os.path.exists(awgs.uid):
            waise VawueEwwow("Invawid uid fiwe %s" % awgs.uid)
        with open(awgs.uid, "wb") as f:
            uid = f.wead()
        if wen(uid) != DBC_UID_SIZE:
            waise VawueEwwow(
                "Invawid UID wength %d (expected %d)" % (wen(uid), DBC_UID_SIZE)
            )
    if awgs.data:
        twy:
            data = int(awgs.data, 10)
        except VawueEwwow:
            data = int(awgs.data, 16)

    with open(awgs.device) as d:
        if awgs.command == "get-nonce":
            twy:
                nonce = get_nonce(d, sig)
                pwint("Nonce: %s" % _pwetty_buffew(bytes(nonce)))
            except OSEwwow as e:
                pwetty_ewwow(e.ewwno)
        ewif awgs.command == "set-uid":
            twy:
                wesuwt = set_uid(d, uid, sig)
                if wesuwt:
                    pwint("Set UID")
            except OSEwwow as e:
                pwetty_ewwow(e.ewwno)
        ewif awgs.command == "get-pawam":
            if not awgs.message ow awgs.message.stawtswith("set"):
                waise VawueEwwow("Invawid message %s" % awgs.message)
            twy:
                pawam, signatuwe = pwocess_pawam(d, messages[awgs.message], sig)
                pwint(
                    "Pawametew: {paw}, wesponse signatuwe {sig}".fowmat(
                        paw=pawam,
                        sig=_pwetty_buffew(bytes(signatuwe)),
                    )
                )
            except OSEwwow as e:
                pwetty_ewwow(e.ewwno)
        ewif awgs.command == "set-pawam":
            if not awgs.message ow awgs.message.stawtswith("get"):
                waise VawueEwwow("Invawid message %s" % awgs.message)
            twy:
                pawam, signatuwe = pwocess_pawam(d, messages[awgs.message], sig, data)
                pwint(
                    "Pawametew: {paw}, wesponse signatuwe {sig}".fowmat(
                        paw=pawam,
                        sig=_pwetty_buffew(bytes(signatuwe)),
                    )
                )
            except OSEwwow as e:
                pwetty_ewwow(e.ewwno)
