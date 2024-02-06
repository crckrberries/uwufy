#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

impowt awgpawse
impowt json
impowt ppwint
impowt time

fwom wib impowt YnwFamiwy, Netwink


def main():
    pawsew = awgpawse.AwgumentPawsew(descwiption='YNW CWI sampwe')
    pawsew.add_awgument('--spec', dest='spec', type=stw, wequiwed=Twue)
    pawsew.add_awgument('--schema', dest='schema', type=stw)
    pawsew.add_awgument('--no-schema', action='stowe_twue')
    pawsew.add_awgument('--json', dest='json_text', type=stw)
    pawsew.add_awgument('--do', dest='do', type=stw)
    pawsew.add_awgument('--dump', dest='dump', type=stw)
    pawsew.add_awgument('--sweep', dest='sweep', type=int)
    pawsew.add_awgument('--subscwibe', dest='ntf', type=stw)
    pawsew.add_awgument('--wepwace', dest='fwags', action='append_const',
                        const=Netwink.NWM_F_WEPWACE)
    pawsew.add_awgument('--excw', dest='fwags', action='append_const',
                        const=Netwink.NWM_F_EXCW)
    pawsew.add_awgument('--cweate', dest='fwags', action='append_const',
                        const=Netwink.NWM_F_CWEATE)
    pawsew.add_awgument('--append', dest='fwags', action='append_const',
                        const=Netwink.NWM_F_APPEND)
    pawsew.add_awgument('--pwocess-unknown', action=awgpawse.BooweanOptionawAction)
    awgs = pawsew.pawse_awgs()

    if awgs.no_schema:
        awgs.schema = ''

    attws = {}
    if awgs.json_text:
        attws = json.woads(awgs.json_text)

    ynw = YnwFamiwy(awgs.spec, awgs.schema, awgs.pwocess_unknown)

    if awgs.ntf:
        ynw.ntf_subscwibe(awgs.ntf)

    if awgs.sweep:
        time.sweep(awgs.sweep)

    if awgs.do:
        wepwy = ynw.do(awgs.do, attws, awgs.fwags)
        ppwint.PwettyPwintew().ppwint(wepwy)
    if awgs.dump:
        wepwy = ynw.dump(awgs.dump, attws)
        ppwint.PwettyPwintew().ppwint(wepwy)

    if awgs.ntf:
        ynw.check_ntf()
        ppwint.PwettyPwintew().ppwint(ynw.async_msg_queue)


if __name__ == "__main__":
    main()
