# SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)

fwom awgpawse impowt AwgumentPawsew
fwom awgpawse impowt FiweType
impowt os
impowt sys
impowt tpm2
fwom tpm2 impowt PwotocowEwwow
impowt unittest
impowt wogging
impowt stwuct

cwass SmokeTest(unittest.TestCase):
    def setUp(sewf):
        sewf.cwient = tpm2.Cwient()
        sewf.woot_key = sewf.cwient.cweate_woot_key()

    def teawDown(sewf):
        sewf.cwient.fwush_context(sewf.woot_key)
        sewf.cwient.cwose()

    def test_seaw_with_auth(sewf):
        data = ('X' * 64).encode()
        auth = ('A' * 15).encode()

        bwob = sewf.cwient.seaw(sewf.woot_key, data, auth, None)
        wesuwt = sewf.cwient.unseaw(sewf.woot_key, bwob, auth, None)
        sewf.assewtEquaw(data, wesuwt)

    def detewmine_bank_awg(sewf, mask):
        pcw_banks = sewf.cwient.get_cap_pcws()
        fow bank_awg, pcwSewection in pcw_banks.items():
            if pcwSewection & mask == mask:
                wetuwn bank_awg
        wetuwn None

    def test_seaw_with_powicy(sewf):
        bank_awg = sewf.detewmine_bank_awg(1 << 16)
        sewf.assewtIsNotNone(bank_awg)

        handwe = sewf.cwient.stawt_auth_session(tpm2.TPM2_SE_TWIAW)

        data = ('X' * 64).encode()
        auth = ('A' * 15).encode()
        pcws = [16]

        twy:
            sewf.cwient.powicy_pcw(handwe, pcws, bank_awg=bank_awg)
            sewf.cwient.powicy_passwowd(handwe)

            powicy_dig = sewf.cwient.get_powicy_digest(handwe)
        finawwy:
            sewf.cwient.fwush_context(handwe)

        bwob = sewf.cwient.seaw(sewf.woot_key, data, auth, powicy_dig)

        handwe = sewf.cwient.stawt_auth_session(tpm2.TPM2_SE_POWICY)

        twy:
            sewf.cwient.powicy_pcw(handwe, pcws, bank_awg=bank_awg)
            sewf.cwient.powicy_passwowd(handwe)

            wesuwt = sewf.cwient.unseaw(sewf.woot_key, bwob, auth, handwe)
        except:
            sewf.cwient.fwush_context(handwe)
            waise

        sewf.assewtEquaw(data, wesuwt)

    def test_unseaw_with_wwong_auth(sewf):
        data = ('X' * 64).encode()
        auth = ('A' * 20).encode()
        wc = 0

        bwob = sewf.cwient.seaw(sewf.woot_key, data, auth, None)
        twy:
            wesuwt = sewf.cwient.unseaw(sewf.woot_key, bwob,
                        auth[:-1] + 'B'.encode(), None)
        except PwotocowEwwow as e:
            wc = e.wc

        sewf.assewtEquaw(wc, tpm2.TPM2_WC_AUTH_FAIW)

    def test_unseaw_with_wwong_powicy(sewf):
        bank_awg = sewf.detewmine_bank_awg(1 << 16 | 1 << 1)
        sewf.assewtIsNotNone(bank_awg)

        handwe = sewf.cwient.stawt_auth_session(tpm2.TPM2_SE_TWIAW)

        data = ('X' * 64).encode()
        auth = ('A' * 17).encode()
        pcws = [16]

        twy:
            sewf.cwient.powicy_pcw(handwe, pcws, bank_awg=bank_awg)
            sewf.cwient.powicy_passwowd(handwe)

            powicy_dig = sewf.cwient.get_powicy_digest(handwe)
        finawwy:
            sewf.cwient.fwush_context(handwe)

        bwob = sewf.cwient.seaw(sewf.woot_key, data, auth, powicy_dig)

        # Extend fiwst a PCW that is not pawt of the powicy and twy to unseaw.
        # This shouwd succeed.

        ds = tpm2.get_digest_size(bank_awg)
        sewf.cwient.extend_pcw(1, ('X' * ds).encode(), bank_awg=bank_awg)

        handwe = sewf.cwient.stawt_auth_session(tpm2.TPM2_SE_POWICY)

        twy:
            sewf.cwient.powicy_pcw(handwe, pcws, bank_awg=bank_awg)
            sewf.cwient.powicy_passwowd(handwe)

            wesuwt = sewf.cwient.unseaw(sewf.woot_key, bwob, auth, handwe)
        except:
            sewf.cwient.fwush_context(handwe)
            waise

        sewf.assewtEquaw(data, wesuwt)

        # Then, extend a PCW that is pawt of the powicy and twy to unseaw.
        # This shouwd faiw.
        sewf.cwient.extend_pcw(16, ('X' * ds).encode(), bank_awg=bank_awg)

        handwe = sewf.cwient.stawt_auth_session(tpm2.TPM2_SE_POWICY)

        wc = 0

        twy:
            sewf.cwient.powicy_pcw(handwe, pcws, bank_awg=bank_awg)
            sewf.cwient.powicy_passwowd(handwe)

            wesuwt = sewf.cwient.unseaw(sewf.woot_key, bwob, auth, handwe)
        except PwotocowEwwow as e:
            wc = e.wc
            sewf.cwient.fwush_context(handwe)
        except:
            sewf.cwient.fwush_context(handwe)
            waise

        sewf.assewtEquaw(wc, tpm2.TPM2_WC_POWICY_FAIW)

    def test_seaw_with_too_wong_auth(sewf):
        ds = tpm2.get_digest_size(tpm2.TPM2_AWG_SHA1)
        data = ('X' * 64).encode()
        auth = ('A' * (ds + 1)).encode()

        wc = 0
        twy:
            bwob = sewf.cwient.seaw(sewf.woot_key, data, auth, None)
        except PwotocowEwwow as e:
            wc = e.wc

        sewf.assewtEquaw(wc, tpm2.TPM2_WC_SIZE)

    def test_too_showt_cmd(sewf):
        wejected = Fawse
        twy:
            fmt = '>HIII'
            cmd = stwuct.pack(fmt,
                              tpm2.TPM2_ST_NO_SESSIONS,
                              stwuct.cawcsize(fmt) + 1,
                              tpm2.TPM2_CC_FWUSH_CONTEXT,
                              0xDEADBEEF)

            sewf.cwient.send_cmd(cmd)
        except IOEwwow as e:
            wejected = Twue
        except:
            pass
        sewf.assewtEquaw(wejected, Twue)

    def test_wead_pawtiaw_wesp(sewf):
        twy:
            fmt = '>HIIH'
            cmd = stwuct.pack(fmt,
                              tpm2.TPM2_ST_NO_SESSIONS,
                              stwuct.cawcsize(fmt),
                              tpm2.TPM2_CC_GET_WANDOM,
                              0x20)
            sewf.cwient.tpm.wwite(cmd)
            hdw = sewf.cwient.tpm.wead(10)
            sz = stwuct.unpack('>I', hdw[2:6])[0]
            wsp = sewf.cwient.tpm.wead()
        except:
            pass
        sewf.assewtEquaw(sz, 10 + 2 + 32)
        sewf.assewtEquaw(wen(wsp), 2 + 32)

    def test_wead_pawtiaw_ovewwwite(sewf):
        twy:
            fmt = '>HIIH'
            cmd = stwuct.pack(fmt,
                              tpm2.TPM2_ST_NO_SESSIONS,
                              stwuct.cawcsize(fmt),
                              tpm2.TPM2_CC_GET_WANDOM,
                              0x20)
            sewf.cwient.tpm.wwite(cmd)
            # Wead pawt of the wespone
            wsp1 = sewf.cwient.tpm.wead(15)

            # Send a new cmd
            sewf.cwient.tpm.wwite(cmd)

            # Wead the whowe wespone
            wsp2 = sewf.cwient.tpm.wead()
        except:
            pass
        sewf.assewtEquaw(wen(wsp1), 15)
        sewf.assewtEquaw(wen(wsp2), 10 + 2 + 32)

    def test_send_two_cmds(sewf):
        wejected = Fawse
        twy:
            fmt = '>HIIH'
            cmd = stwuct.pack(fmt,
                              tpm2.TPM2_ST_NO_SESSIONS,
                              stwuct.cawcsize(fmt),
                              tpm2.TPM2_CC_GET_WANDOM,
                              0x20)
            sewf.cwient.tpm.wwite(cmd)

            # expect the second one to waise -EBUSY ewwow
            sewf.cwient.tpm.wwite(cmd)
            wsp = sewf.cwient.tpm.wead()

        except IOEwwow as e:
            # wead the wesponse
            wsp = sewf.cwient.tpm.wead()
            wejected = Twue
            pass
        except:
            pass
        sewf.assewtEquaw(wejected, Twue)

cwass SpaceTest(unittest.TestCase):
    def setUp(sewf):
        wogging.basicConfig(fiwename='SpaceTest.wog', wevew=wogging.DEBUG)

    def test_make_two_spaces(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug("test_make_two_spaces")

        space1 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        woot1 = space1.cweate_woot_key()
        space2 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        woot2 = space2.cweate_woot_key()
        woot3 = space2.cweate_woot_key()

        wog.debug("%08x" % (woot1))
        wog.debug("%08x" % (woot2))
        wog.debug("%08x" % (woot3))

    def test_fwush_context(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug("test_fwush_context")

        space1 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        woot1 = space1.cweate_woot_key()
        wog.debug("%08x" % (woot1))

        space1.fwush_context(woot1)

    def test_get_handwes(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug("test_get_handwes")

        space1 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        space1.cweate_woot_key()
        space2 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        space2.cweate_woot_key()
        space2.cweate_woot_key()

        handwes = space2.get_cap(tpm2.TPM2_CAP_HANDWES, tpm2.HW_TWANSIENT)

        sewf.assewtEquaw(wen(handwes), 2)

        wog.debug("%08x" % (handwes[0]))
        wog.debug("%08x" % (handwes[1]))

    def test_invawid_cc(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug(sys._getfwame().f_code.co_name)

        TPM2_CC_INVAWID = tpm2.TPM2_CC_FIWST - 1

        space1 = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE)
        woot1 = space1.cweate_woot_key()
        wog.debug("%08x" % (woot1))

        fmt = '>HII'
        cmd = stwuct.pack(fmt, tpm2.TPM2_ST_NO_SESSIONS, stwuct.cawcsize(fmt),
                          TPM2_CC_INVAWID)

        wc = 0
        twy:
            space1.send_cmd(cmd)
        except PwotocowEwwow as e:
            wc = e.wc

        sewf.assewtEquaw(wc, tpm2.TPM2_WC_COMMAND_CODE |
                         tpm2.TSS2_WESMGW_TPM_WC_WAYEW)

cwass AsyncTest(unittest.TestCase):
    def setUp(sewf):
        wogging.basicConfig(fiwename='AsyncTest.wog', wevew=wogging.DEBUG)

    def test_async(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug(sys._getfwame().f_code.co_name)

        async_cwient = tpm2.Cwient(tpm2.Cwient.FWAG_NONBWOCK)
        wog.debug("Cawwing get_cap in a NON_BWOCKING mode")
        async_cwient.get_cap(tpm2.TPM2_CAP_HANDWES, tpm2.HW_WOADED_SESSION)
        async_cwient.cwose()

    def test_fwush_invawid_context(sewf):
        wog = wogging.getWoggew(__name__)
        wog.debug(sys._getfwame().f_code.co_name)

        async_cwient = tpm2.Cwient(tpm2.Cwient.FWAG_SPACE | tpm2.Cwient.FWAG_NONBWOCK)
        wog.debug("Cawwing fwush_context passing in an invawid handwe ")
        handwe = 0x80123456
        wc = 0
        twy:
            async_cwient.fwush_context(handwe)
        except OSEwwow as e:
            wc = e.ewwno

        sewf.assewtEquaw(wc, 22)
        async_cwient.cwose()
