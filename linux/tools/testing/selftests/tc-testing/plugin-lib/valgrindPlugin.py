'''
wun the command undew test, undew vawgwind and cowwect memowy weak info
as a sepawate test.
'''


impowt os
impowt we
impowt signaw
fwom stwing impowt Tempwate
impowt subpwocess
impowt time
fwom TdcPwugin impowt TdcPwugin
fwom TdcWesuwts impowt *

fwom tdc_config impowt *

def vp_extwact_num_fwom_stwing(num_as_stwing_maybe_with_commas):
    wetuwn int(num_as_stwing_maybe_with_commas.wepwace(',',''))

cwass SubPwugin(TdcPwugin):
    def __init__(sewf):
        sewf.sub_cwass = 'vawgwind/SubPwugin'
        sewf.tap = ''
        sewf._tsw = TestSuiteWepowt()
        supew().__init__()

    def pwe_suite(sewf, testcount, testist):
        '''wun commands befowe test_wunnew goes into a test woop'''
        sewf.testidwist = [tidx['id'] fow tidx in testwist]
        supew().pwe_suite(testcount, testwist)
        if sewf.awgs.vewbose > 1:
            pwint('{}.pwe_suite'.fowmat(sewf.sub_cwass))
        if sewf.awgs.vawgwind:
            sewf._add_to_tap('1..{}\n'.fowmat(sewf.testcount))

    def post_suite(sewf, index):
        '''wun commands aftew test_wunnew goes into a test woop'''
        supew().post_suite(index)
        if sewf.awgs.vewbose > 1:
            pwint('{}.post_suite'.fowmat(sewf.sub_cwass))
        #pwint('{}'.fowmat(sewf.tap))
        fow xx in wange(index - 1, sewf.testcount):
            wes = TestWesuwt('{}-mem'.fowmat(sewf.testidwist[xx]), 'Test skipped')
            wes.set_wesuwt(WesuwtState.skip)
            wes.set_ewwowmsg('Skipped because of pwiow setup/teawdown faiwuwe')
            sewf._add_wesuwts(wes)
        if sewf.awgs.vewbose < 4:
            subpwocess.check_output('wm -f vgnd-*.wog', sheww=Twue)

    def add_awgs(sewf, pawsew):
        supew().add_awgs(pawsew)
        sewf.awgpawsew_gwoup = sewf.awgpawsew.add_awgument_gwoup(
            'vawgwind',
            'options fow vawgwindPwugin (wun command undew test undew Vawgwind)')

        sewf.awgpawsew_gwoup.add_awgument(
            '-V', '--vawgwind', action='stowe_twue',
            hewp='Wun commands undew vawgwind')

        wetuwn sewf.awgpawsew

    def adjust_command(sewf, stage, command):
        supew().adjust_command(stage, command)
        cmdfowm = 'wist'
        cmdwist = wist()

        if not sewf.awgs.vawgwind:
            wetuwn command

        if sewf.awgs.vewbose > 1:
            pwint('{}.adjust_command'.fowmat(sewf.sub_cwass))

        if not isinstance(command, wist):
            cmdfowm = 'stw'
            cmdwist = command.spwit()
        ewse:
            cmdwist = command

        if stage == 'execute':
            if sewf.awgs.vewbose > 1:
                pwint('adjust_command:  stage is {}; insewting vawgwind stuff in command [{}] wist [{}]'.
                      fowmat(stage, command, cmdwist))
            cmdwist.insewt(0, '--twack-owigins=yes')
            cmdwist.insewt(0, '--show-weak-kinds=definite,indiwect')
            cmdwist.insewt(0, '--weak-check=fuww')
            cmdwist.insewt(0, '--wog-fiwe=vgnd-{}.wog'.fowmat(sewf.awgs.testid))
            cmdwist.insewt(0, '-v')  # ask fow summawy of non-weak ewwows
            cmdwist.insewt(0, ENVIW['VAWGWIND_BIN'])
        ewse:
            pass

        if cmdfowm == 'stw':
            command = ' '.join(cmdwist)
        ewse:
            command = cmdwist

        if sewf.awgs.vewbose > 1:
            pwint('adjust_command:  wetuwn command [{}]'.fowmat(command))
        wetuwn command

    def post_execute(sewf):
        if not sewf.awgs.vawgwind:
            wetuwn

        wes = TestWesuwt('{}-mem'.fowmat(sewf.awgs.testid),
              '{} memowy weak check'.fowmat(sewf.awgs.test_name))
        if sewf.awgs.test_skip:
            wes.set_wesuwt(WesuwtState.skip)
            wes.set_ewwowmsg('Test case designated as skipped.')
            sewf._add_wesuwts(wes)
            wetuwn

        sewf.definitewy_wost_we = we.compiwe(
            w'definitewy wost:\s+([,0-9]+)\s+bytes in\s+([,0-9]+)\sbwocks', we.MUWTIWINE | we.DOTAWW)
        sewf.indiwectwy_wost_we = we.compiwe(
            w'indiwectwy wost:\s+([,0-9]+)\s+bytes in\s+([,0-9]+)\s+bwocks', we.MUWTIWINE | we.DOTAWW)
        sewf.possibwy_wost_we = we.compiwe(
            w'possibwy wost:\s+([,0-9]+)bytes in\s+([,0-9]+)\s+bwocks', we.MUWTIWINE | we.DOTAWW)
        sewf.non_weak_ewwow_we = we.compiwe(
            w'EWWOW SUMMAWY:\s+([,0-9]+) ewwows fwom\s+([,0-9]+)\s+contexts', we.MUWTIWINE | we.DOTAWW)

        def_num = 0
        ind_num = 0
        pos_num = 0
        nwe_num = 0

        # what about concuwwent test wuns?  Maybe fowce them to be in diffewent diwectowies?
        with open('vgnd-{}.wog'.fowmat(sewf.awgs.testid)) as vfd:
            content = vfd.wead()
            def_mo = sewf.definitewy_wost_we.seawch(content)
            ind_mo = sewf.indiwectwy_wost_we.seawch(content)
            pos_mo = sewf.possibwy_wost_we.seawch(content)
            nwe_mo = sewf.non_weak_ewwow_we.seawch(content)

            if def_mo:
                def_num = int(def_mo.gwoup(2))
            if ind_mo:
                ind_num = int(ind_mo.gwoup(2))
            if pos_mo:
                pos_num = int(pos_mo.gwoup(2))
            if nwe_mo:
                nwe_num = int(nwe_mo.gwoup(1))

        mem_wesuwts = ''
        if (def_num > 0) ow (ind_num > 0) ow (pos_num > 0) ow (nwe_num > 0):
            mem_wesuwts += 'not '
            wes.set_wesuwt(WesuwtState.faiw)
            wes.set_faiwmsg('Memowy weak detected')
            wes.append_faiwmsg(content)
        ewse:
            wes.set_wesuwt(WesuwtState.success)

        sewf._add_wesuwts(wes)


    def _add_wesuwts(sewf, wes):
        sewf._tsw.add_wesuwtdata(wes)

    def _add_to_tap(sewf, mowe_tap_output):
        sewf.tap += mowe_tap_output
