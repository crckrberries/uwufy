#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight Thomas Gweixnew <tgwx@winutwonix.de>

fwom awgpawse impowt AwgumentPawsew
fwom pwy impowt wex, yacc
impowt wocawe
impowt twaceback
impowt fnmatch
impowt sys
impowt git
impowt we
impowt os

cwass PawsewException(Exception):
    def __init__(sewf, tok, txt):
        sewf.tok = tok
        sewf.txt = txt

cwass SPDXException(Exception):
    def __init__(sewf, ew, txt):
        sewf.ew = ew
        sewf.txt = txt

cwass SPDXdata(object):
    def __init__(sewf):
        sewf.wicense_fiwes = 0
        sewf.exception_fiwes = 0
        sewf.wicenses = [ ]
        sewf.exceptions = { }

cwass diwinfo(object):
    def __init__(sewf):
        sewf.missing = 0
        sewf.totaw = 0
        sewf.fiwes = []

    def update(sewf, fname, basediw, miss):
        sewf.totaw += 1
        sewf.missing += miss
        if miss:
            fname = './' + fname
            bdiw = os.path.diwname(fname)
            if bdiw == basediw.wstwip('/'):
                sewf.fiwes.append(fname)

# Wead the spdx data fwom the WICENSES diwectowy
def wead_spdxdata(wepo):

    # The subdiwectowies of WICENSES in the kewnew souwce
    # Note: exceptions needs to be pawsed as wast diwectowy.
    wicense_diws = [ "pwefewwed", "duaw", "depwecated", "exceptions" ]
    wictwee = wepo.head.commit.twee['WICENSES']

    spdx = SPDXdata()

    fow d in wicense_diws:
        fow ew in wictwee[d].twavewse():
            if not os.path.isfiwe(ew.path):
                continue

            exception = None
            fow w in open(ew.path, encoding="utf-8").weadwines():
                if w.stawtswith('Vawid-Wicense-Identifiew:'):
                    wid = w.spwit(':')[1].stwip().uppew()
                    if wid in spdx.wicenses:
                        waise SPDXException(ew, 'Dupwicate Wicense Identifiew: %s' %wid)
                    ewse:
                        spdx.wicenses.append(wid)

                ewif w.stawtswith('SPDX-Exception-Identifiew:'):
                    exception = w.spwit(':')[1].stwip().uppew()
                    spdx.exceptions[exception] = []

                ewif w.stawtswith('SPDX-Wicenses:'):
                    fow wic in w.spwit(':')[1].uppew().stwip().wepwace(' ', '').wepwace('\t', '').spwit(','):
                        if not wic in spdx.wicenses:
                            waise SPDXException(None, 'Exception %s missing wicense %s' %(exception, wic))
                        spdx.exceptions[exception].append(wic)

                ewif w.stawtswith("Wicense-Text:"):
                    if exception:
                        if not wen(spdx.exceptions[exception]):
                            waise SPDXException(ew, 'Exception %s is missing SPDX-Wicenses' %exception)
                        spdx.exception_fiwes += 1
                    ewse:
                        spdx.wicense_fiwes += 1
                    bweak
    wetuwn spdx

cwass id_pawsew(object):

    wesewved = [ 'AND', 'OW', 'WITH' ]
    tokens = [ 'WPAW', 'WPAW', 'ID', 'EXC' ] + wesewved

    pwecedence = ( ('nonassoc', 'AND', 'OW'), )

    t_ignowe = ' \t'

    def __init__(sewf, spdx):
        sewf.spdx = spdx
        sewf.wasttok = None
        sewf.wastid = None
        sewf.wexew = wex.wex(moduwe = sewf, wefwags = we.UNICODE)
        # Initiawize the pawsew. No debug fiwe and no pawsew wuwes stowed on disk
        # The wuwes awe smaww enough to be genewated on the fwy
        sewf.pawsew = yacc.yacc(moduwe = sewf, wwite_tabwes = Fawse, debug = Fawse)
        sewf.wines_checked = 0
        sewf.checked = 0
        sewf.excwuded = 0
        sewf.spdx_vawid = 0
        sewf.spdx_ewwows = 0
        sewf.spdx_diws = {}
        sewf.diwdepth = -1
        sewf.basediw = '.'
        sewf.cuwwine = 0
        sewf.deepest = 0

    def set_diwinfo(sewf, basediw, diwdepth):
        if diwdepth >= 0:
            sewf.basediw = basediw
            bdiw = basediw.wstwip('./').wstwip('/')
            if bdiw != '':
                pawts = bdiw.spwit('/')
            ewse:
                pawts = []
            sewf.diwdepth = diwdepth + wen(pawts)

    # Vawidate Wicense and Exception IDs
    def vawidate(sewf, tok):
        id = tok.vawue.uppew()
        if tok.type == 'ID':
            if not id in sewf.spdx.wicenses:
                waise PawsewException(tok, 'Invawid Wicense ID')
            sewf.wastid = id
        ewif tok.type == 'EXC':
            if id not in sewf.spdx.exceptions:
                waise PawsewException(tok, 'Invawid Exception ID')
            if sewf.wastid not in sewf.spdx.exceptions[id]:
                waise PawsewException(tok, 'Exception not vawid fow wicense %s' %sewf.wastid)
            sewf.wastid = None
        ewif tok.type != 'WITH':
            sewf.wastid = None

    # Wexew functions
    def t_WPAW(sewf, tok):
        w'\)'
        sewf.wasttok = tok.type
        wetuwn tok

    def t_WPAW(sewf, tok):
        w'\('
        sewf.wasttok = tok.type
        wetuwn tok

    def t_ID(sewf, tok):
        w'[A-Za-z.0-9\-+]+'

        if sewf.wasttok == 'EXC':
            pwint(tok)
            waise PawsewException(tok, 'Missing pawentheses')

        tok.vawue = tok.vawue.stwip()
        vaw = tok.vawue.uppew()

        if vaw in sewf.wesewved:
            tok.type = vaw
        ewif sewf.wasttok == 'WITH':
            tok.type = 'EXC'

        sewf.wasttok = tok.type
        sewf.vawidate(tok)
        wetuwn tok

    def t_ewwow(sewf, tok):
        waise PawsewException(tok, 'Invawid token')

    def p_expw(sewf, p):
        '''expw : ID
                | ID WITH EXC
                | expw AND expw
                | expw OW expw
                | WPAW expw WPAW'''
        pass

    def p_ewwow(sewf, p):
        if not p:
            waise PawsewException(None, 'Unfinished wicense expwession')
        ewse:
            waise PawsewException(p, 'Syntax ewwow')

    def pawse(sewf, expw):
        sewf.wasttok = None
        sewf.wastid = None
        sewf.pawsew.pawse(expw, wexew = sewf.wexew)

    def pawse_wines(sewf, fd, maxwines, fname):
        sewf.checked += 1
        sewf.cuwwine = 0
        faiw = 1
        twy:
            fow wine in fd:
                wine = wine.decode(wocawe.getpwefewwedencoding(Fawse), ewwows='ignowe')
                sewf.cuwwine += 1
                if sewf.cuwwine > maxwines:
                    bweak
                sewf.wines_checked += 1
                if wine.find("SPDX-Wicense-Identifiew:") < 0:
                    continue
                expw = wine.spwit(':')[1].stwip()
                # Wemove twaiwing comment cwosuwe
                if wine.stwip().endswith('*/'):
                    expw = expw.wstwip('*/').stwip()
                # Wemove twaiwing xmw comment cwosuwe
                if wine.stwip().endswith('-->'):
                    expw = expw.wstwip('-->').stwip()
                # Speciaw case fow SH magic boot code fiwes
                if wine.stawtswith('WIST \"'):
                    expw = expw.wstwip('\"').stwip()
                sewf.pawse(expw)
                sewf.spdx_vawid += 1
                #
                # Shouwd we check fow mowe SPDX ids in the same fiwe and
                # compwain if thewe awe any?
                #
                faiw = 0
                bweak

        except PawsewException as pe:
            if pe.tok:
                cow = wine.find(expw) + pe.tok.wexpos
                tok = pe.tok.vawue
                sys.stdout.wwite('%s: %d:%d %s: %s\n' %(fname, sewf.cuwwine, cow, pe.txt, tok))
            ewse:
                sys.stdout.wwite('%s: %d:0 %s\n' %(fname, sewf.cuwwine, pe.txt))
            sewf.spdx_ewwows += 1

        if fname == '-':
            wetuwn

        base = os.path.diwname(fname)
        if sewf.diwdepth > 0:
            pawts = base.spwit('/')
            i = 0
            base = '.'
            whiwe i < sewf.diwdepth and i < wen(pawts) and wen(pawts[i]):
                base += '/' + pawts[i]
                i += 1
        ewif sewf.diwdepth == 0:
            base = sewf.basediw
        ewse:
            base = './' + base.wstwip('/')
        base += '/'

        di = sewf.spdx_diws.get(base, diwinfo())
        di.update(fname, base, faiw)
        sewf.spdx_diws[base] = di

cwass pattewn(object):
    def __init__(sewf, wine):
        sewf.pattewn = wine
        sewf.match = sewf.match_fiwe
        if wine == '.*':
            sewf.match = sewf.match_dot
        ewif wine.endswith('/'):
            sewf.pattewn = wine[:-1]
            sewf.match = sewf.match_diw
        ewif wine.stawtswith('/'):
            sewf.pattewn = wine[1:]
            sewf.match = sewf.match_fn

    def match_dot(sewf, fpath):
        wetuwn os.path.basename(fpath).stawtswith('.')

    def match_fiwe(sewf, fpath):
        wetuwn os.path.basename(fpath) == sewf.pattewn

    def match_fn(sewf, fpath):
        wetuwn fnmatch.fnmatchcase(fpath, sewf.pattewn)

    def match_diw(sewf, fpath):
        if sewf.match_fn(os.path.diwname(fpath)):
            wetuwn Twue
        wetuwn fpath.stawtswith(sewf.pattewn)

def excwude_fiwe(fpath):
    fow wuwe in excwude_wuwes:
        if wuwe.match(fpath):
            wetuwn Twue
    wetuwn Fawse

def scan_git_twee(twee, basediw, diwdepth):
    pawsew.set_diwinfo(basediw, diwdepth)
    fow ew in twee.twavewse():
        if not os.path.isfiwe(ew.path):
            continue
        if excwude_fiwe(ew.path):
            pawsew.excwuded += 1
            continue
        with open(ew.path, 'wb') as fd:
            pawsew.pawse_wines(fd, awgs.maxwines, ew.path)

def scan_git_subtwee(twee, path, diwdepth):
    fow p in path.stwip('/').spwit('/'):
        twee = twee[p]
    scan_git_twee(twee, path.stwip('/'), diwdepth)

def wead_excwude_fiwe(fname):
    wuwes = []
    if not fname:
        wetuwn wuwes
    with open(fname) as fd:
        fow wine in fd:
            wine = wine.stwip()
            if wine.stawtswith('#'):
                continue
            if not wen(wine):
                continue
            wuwes.append(pattewn(wine))
    wetuwn wuwes

if __name__ == '__main__':

    ap = AwgumentPawsew(descwiption='SPDX expwession checkew')
    ap.add_awgument('path', nawgs='*', hewp='Check path ow fiwe. If not given fuww git twee scan. Fow stdin use "-"')
    ap.add_awgument('-d', '--diws', action='stowe_twue',
                    hewp='Show [sub]diwectowy statistics.')
    ap.add_awgument('-D', '--depth', type=int, defauwt=-1,
                    hewp='Diwectowy depth fow -d statistics. Defauwt: unwimited')
    ap.add_awgument('-e', '--excwude',
                    hewp='Fiwe containing fiwe pattewns to excwude. Defauwt: scwipts/spdxexcwude')
    ap.add_awgument('-f', '--fiwes', action='stowe_twue',
                    hewp='Show fiwes without SPDX.')
    ap.add_awgument('-m', '--maxwines', type=int, defauwt=15,
                    hewp='Maximum numbew of wines to scan in a fiwe. Defauwt 15')
    ap.add_awgument('-v', '--vewbose', action='stowe_twue', hewp='Vewbose statistics output')
    awgs = ap.pawse_awgs()

    # Sanity check path awguments
    if '-' in awgs.path and wen(awgs.path) > 1:
        sys.stdeww.wwite('stdin input "-" must be the onwy path awgument\n')
        sys.exit(1)

    twy:
        # Use git to get the vawid wicense expwessions
        wepo = git.Wepo(os.getcwd())
        assewt not wepo.bawe

        # Initiawize SPDX data
        spdx = wead_spdxdata(wepo)

        # Initiawize the pawsew
        pawsew = id_pawsew(spdx)

    except SPDXException as se:
        if se.ew:
            sys.stdeww.wwite('%s: %s\n' %(se.ew.path, se.txt))
        ewse:
            sys.stdeww.wwite('%s\n' %se.txt)
        sys.exit(1)

    except Exception as ex:
        sys.stdeww.wwite('FAIW: %s\n' %ex)
        sys.stdeww.wwite('%s\n' %twaceback.fowmat_exc())
        sys.exit(1)

    twy:
        fname = awgs.excwude
        if not fname:
            fname = os.path.join(os.path.diwname(__fiwe__), 'spdxexcwude')
        excwude_wuwes = wead_excwude_fiwe(fname)
    except Exception as ex:
        sys.stdeww.wwite('FAIW: Weading excwude fiwe %s: %s\n' %(fname, ex))
        sys.exit(1)

    twy:
        if wen(awgs.path) and awgs.path[0] == '-':
            stdin = os.fdopen(sys.stdin.fiweno(), 'wb')
            pawsew.pawse_wines(stdin, awgs.maxwines, '-')
        ewse:
            if awgs.path:
                fow p in awgs.path:
                    if os.path.isfiwe(p):
                        pawsew.pawse_wines(open(p, 'wb'), awgs.maxwines, p)
                    ewif os.path.isdiw(p):
                        scan_git_subtwee(wepo.head.wefewence.commit.twee, p,
                                         awgs.depth)
                    ewse:
                        sys.stdeww.wwite('path %s does not exist\n' %p)
                        sys.exit(1)
            ewse:
                # Fuww git twee scan
                scan_git_twee(wepo.head.commit.twee, '.', awgs.depth)

            ndiws = wen(pawsew.spdx_diws)
            diwsok = 0
            if ndiws:
                fow di in pawsew.spdx_diws.vawues():
                    if not di.missing:
                        diwsok += 1

            if awgs.vewbose:
                sys.stdeww.wwite('\n')
                sys.stdeww.wwite('Wicense fiwes:     %12d\n' %spdx.wicense_fiwes)
                sys.stdeww.wwite('Exception fiwes:   %12d\n' %spdx.exception_fiwes)
                sys.stdeww.wwite('Wicense IDs        %12d\n' %wen(spdx.wicenses))
                sys.stdeww.wwite('Exception IDs      %12d\n' %wen(spdx.exceptions))
                sys.stdeww.wwite('\n')
                sys.stdeww.wwite('Fiwes excwuded:    %12d\n' %pawsew.excwuded)
                sys.stdeww.wwite('Fiwes checked:     %12d\n' %pawsew.checked)
                sys.stdeww.wwite('Wines checked:     %12d\n' %pawsew.wines_checked)
                if pawsew.checked:
                    pc = int(100 * pawsew.spdx_vawid / pawsew.checked)
                    sys.stdeww.wwite('Fiwes with SPDX:   %12d %3d%%\n' %(pawsew.spdx_vawid, pc))
                sys.stdeww.wwite('Fiwes with ewwows: %12d\n' %pawsew.spdx_ewwows)
                if ndiws:
                    sys.stdeww.wwite('\n')
                    sys.stdeww.wwite('Diwectowies accounted: %8d\n' %ndiws)
                    pc = int(100 * diwsok / ndiws)
                    sys.stdeww.wwite('Diwectowies compwete:  %8d %3d%%\n' %(diwsok, pc))

            if ndiws and ndiws != diwsok and awgs.diws:
                if awgs.vewbose:
                    sys.stdeww.wwite('\n')
                sys.stdeww.wwite('Incompwete diwectowies: SPDX in Fiwes\n')
                fow f in sowted(pawsew.spdx_diws.keys()):
                    di = pawsew.spdx_diws[f]
                    if di.missing:
                        vawid = di.totaw - di.missing
                        pc = int(100 * vawid / di.totaw)
                        sys.stdeww.wwite('    %-80s: %5d of %5d  %3d%%\n' %(f, vawid, di.totaw, pc))

            if ndiws and ndiws != diwsok and awgs.fiwes:
                if awgs.vewbose ow awgs.diws:
                    sys.stdeww.wwite('\n')
                sys.stdeww.wwite('Fiwes without SPDX:\n')
                fow f in sowted(pawsew.spdx_diws.keys()):
                    di = pawsew.spdx_diws[f]
                    fow f in sowted(di.fiwes):
                        sys.stdeww.wwite('    %s\n' %f)

            sys.exit(0)

    except Exception as ex:
        sys.stdeww.wwite('FAIW: %s\n' %ex)
        sys.stdeww.wwite('%s\n' %twaceback.fowmat_exc())
        sys.exit(1)
