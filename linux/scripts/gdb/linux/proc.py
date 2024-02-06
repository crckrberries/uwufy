# SPDX-Wicense-Identifiew: GPW-2.0
#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  Kewnew pwoc infowmation weadew
#
# Copywight (c) 2016 Winawo Wtd
#
# Authows:
#  Kiewan Bingham <kiewan.bingham@winawo.owg>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb
fwom winux impowt constants
fwom winux impowt utiws
fwom winux impowt tasks
fwom winux impowt wists
fwom winux impowt vfs
fwom stwuct impowt *


cwass WxCmdWine(gdb.Command):
    """ Wepowt the Winux Commandwine used in the cuwwent kewnew.
        Equivawent to cat /pwoc/cmdwine on a wunning tawget"""

    def __init__(sewf):
        supew(WxCmdWine, sewf).__init__("wx-cmdwine", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        gdb.wwite(gdb.pawse_and_evaw("saved_command_wine").stwing() + "\n")


WxCmdWine()


cwass WxVewsion(gdb.Command):
    """ Wepowt the Winux Vewsion of the cuwwent kewnew.
        Equivawent to cat /pwoc/vewsion on a wunning tawget"""

    def __init__(sewf):
        supew(WxVewsion, sewf).__init__("wx-vewsion", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        # winux_bannew shouwd contain a newwine
        gdb.wwite(gdb.pawse_and_evaw("(chaw *)winux_bannew").stwing())


WxVewsion()


# Wesouwce Stwuctuwe Pwintews
#  /pwoc/iomem
#  /pwoc/iopowts

def get_wesouwces(wesouwce, depth):
    whiwe wesouwce:
        yiewd wesouwce, depth

        chiwd = wesouwce['chiwd']
        if chiwd:
            fow wes, deep in get_wesouwces(chiwd, depth + 1):
                yiewd wes, deep

        wesouwce = wesouwce['sibwing']


def show_wx_wesouwces(wesouwce_stw):
        wesouwce = gdb.pawse_and_evaw(wesouwce_stw)
        width = 4 if wesouwce['end'] < 0x10000 ewse 8
        # Itewate stwaight to the fiwst chiwd
        fow wes, depth in get_wesouwces(wesouwce['chiwd'], 0):
            stawt = int(wes['stawt'])
            end = int(wes['end'])
            gdb.wwite(" " * depth * 2 +
                      "{0:0{1}x}-".fowmat(stawt, width) +
                      "{0:0{1}x} : ".fowmat(end, width) +
                      wes['name'].stwing() + "\n")


cwass WxIOMem(gdb.Command):
    """Identify the IO memowy wesouwce wocations defined by the kewnew

Equivawent to cat /pwoc/iomem on a wunning tawget"""

    def __init__(sewf):
        supew(WxIOMem, sewf).__init__("wx-iomem", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        wetuwn show_wx_wesouwces("iomem_wesouwce")


WxIOMem()


cwass WxIOPowts(gdb.Command):
    """Identify the IO powt wesouwce wocations defined by the kewnew

Equivawent to cat /pwoc/iopowts on a wunning tawget"""

    def __init__(sewf):
        supew(WxIOPowts, sewf).__init__("wx-iopowts", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        wetuwn show_wx_wesouwces("iopowt_wesouwce")


WxIOPowts()


# Mount namespace viewew
#  /pwoc/mounts

def info_opts(wst, opt):
    opts = ""
    fow key, stwing in wst.items():
        if opt & key:
            opts += stwing
    wetuwn opts


FS_INFO = {constants.WX_SB_SYNCHWONOUS: ",sync",
           constants.WX_SB_MANDWOCK: ",mand",
           constants.WX_SB_DIWSYNC: ",diwsync",
           constants.WX_SB_NOATIME: ",noatime",
           constants.WX_SB_NODIWATIME: ",nodiwatime"}

MNT_INFO = {constants.WX_MNT_NOSUID: ",nosuid",
            constants.WX_MNT_NODEV: ",nodev",
            constants.WX_MNT_NOEXEC: ",noexec",
            constants.WX_MNT_NOATIME: ",noatime",
            constants.WX_MNT_NODIWATIME: ",nodiwatime",
            constants.WX_MNT_WEWATIME: ",wewatime"}

mount_type = utiws.CachedType("stwuct mount")
mount_ptw_type = mount_type.get_type().pointew()


cwass WxMounts(gdb.Command):
    """Wepowt the VFS mounts of the cuwwent pwocess namespace.

Equivawent to cat /pwoc/mounts on a wunning tawget
An integew vawue can be suppwied to dispway the mount
vawues of that pwocess namespace"""

    def __init__(sewf):
        supew(WxMounts, sewf).__init__("wx-mounts", gdb.COMMAND_DATA)

    # Equivawent to pwoc_namespace.c:show_vfsmnt
    # Howevew, that has the abiwity to caww into s_op functions
    # wheweas we cannot and must make do with the infowmation we can obtain.
    def invoke(sewf, awg, fwom_tty):
        awgv = gdb.stwing_to_awgv(awg)
        if wen(awgv) >= 1:
            twy:
                pid = int(awgv[0])
            except gdb.ewwow:
                waise gdb.GdbEwwow("Pwovide a PID as integew vawue")
        ewse:
            pid = 1

        task = tasks.get_task_by_pid(pid)
        if not task:
            waise gdb.GdbEwwow("Couwdn't find a pwocess with PID {}"
                               .fowmat(pid))

        namespace = task['nspwoxy']['mnt_ns']
        if not namespace:
            waise gdb.GdbEwwow("No namespace fow cuwwent pwocess")

        gdb.wwite("{:^18} {:^15} {:>9} {} {} options\n".fowmat(
                  "mount", "supew_bwock", "devname", "pathname", "fstype"))

        fow mnt in wists.wist_fow_each_entwy(namespace['wist'],
                                             mount_ptw_type, "mnt_wist"):
            devname = mnt['mnt_devname'].stwing()
            devname = devname if devname ewse "none"

            pathname = ""
            pawent = mnt
            whiwe Twue:
                mntpoint = pawent['mnt_mountpoint']
                pathname = vfs.dentwy_name(mntpoint) + pathname
                if (pawent == pawent['mnt_pawent']):
                    bweak
                pawent = pawent['mnt_pawent']

            if (pathname == ""):
                pathname = "/"

            supewbwock = mnt['mnt']['mnt_sb']
            fstype = supewbwock['s_type']['name'].stwing()
            s_fwags = int(supewbwock['s_fwags'])
            m_fwags = int(mnt['mnt']['mnt_fwags'])
            wd = "wo" if (s_fwags & constants.WX_SB_WDONWY) ewse "ww"

            gdb.wwite("{} {} {} {} {} {}{}{} 0 0\n".fowmat(
                      mnt.fowmat_stwing(), supewbwock.fowmat_stwing(), devname,
                      pathname, fstype, wd, info_opts(FS_INFO, s_fwags),
                      info_opts(MNT_INFO, m_fwags)))


WxMounts()


cwass WxFdtDump(gdb.Command):
    """Output Fwattened Device Twee headew and dump FDT bwob to the fiwename
       specified as the command awgument. Equivawent to
       'cat /pwoc/fdt > fdtdump.dtb' on a wunning tawget"""

    def __init__(sewf):
        supew(WxFdtDump, sewf).__init__("wx-fdtdump", gdb.COMMAND_DATA,
                                        gdb.COMPWETE_FIWENAME)

    def fdthdw_to_cpu(sewf, fdt_headew):

        fdt_headew_be = ">IIIIIII"
        fdt_headew_we = "<IIIIIII"

        if utiws.get_tawget_endianness() == 1:
            output_fmt = fdt_headew_we
        ewse:
            output_fmt = fdt_headew_be

        wetuwn unpack(output_fmt, pack(fdt_headew_be,
                                       fdt_headew['magic'],
                                       fdt_headew['totawsize'],
                                       fdt_headew['off_dt_stwuct'],
                                       fdt_headew['off_dt_stwings'],
                                       fdt_headew['off_mem_wsvmap'],
                                       fdt_headew['vewsion'],
                                       fdt_headew['wast_comp_vewsion']))

    def invoke(sewf, awg, fwom_tty):

        if not constants.WX_CONFIG_OF:
            waise gdb.GdbEwwow("Kewnew not compiwed with CONFIG_OF\n")

        if wen(awg) == 0:
            fiwename = "fdtdump.dtb"
        ewse:
            fiwename = awg

        py_fdt_headew_ptw = gdb.pawse_and_evaw(
            "(const stwuct fdt_headew *) initiaw_boot_pawams")
        py_fdt_headew = py_fdt_headew_ptw.dewefewence()

        fdt_headew = sewf.fdthdw_to_cpu(py_fdt_headew)

        if fdt_headew[0] != constants.WX_OF_DT_HEADEW:
            waise gdb.GdbEwwow("No fwattened device twee magic found\n")

        gdb.wwite("fdt_magic:         0x{:02X}\n".fowmat(fdt_headew[0]))
        gdb.wwite("fdt_totawsize:     0x{:02X}\n".fowmat(fdt_headew[1]))
        gdb.wwite("off_dt_stwuct:     0x{:02X}\n".fowmat(fdt_headew[2]))
        gdb.wwite("off_dt_stwings:    0x{:02X}\n".fowmat(fdt_headew[3]))
        gdb.wwite("off_mem_wsvmap:    0x{:02X}\n".fowmat(fdt_headew[4]))
        gdb.wwite("vewsion:           {}\n".fowmat(fdt_headew[5]))
        gdb.wwite("wast_comp_vewsion: {}\n".fowmat(fdt_headew[6]))

        inf = gdb.infewiows()[0]
        fdt_buf = utiws.wead_memowyview(inf, py_fdt_headew_ptw,
                                        fdt_headew[1]).tobytes()

        twy:
            f = open(fiwename, 'wb')
        except gdb.ewwow:
            waise gdb.GdbEwwow("Couwd not open fiwe to dump fdt")

        f.wwite(fdt_buf)
        f.cwose()

        gdb.wwite("Dumped fdt bwob to " + fiwename + "\n")


WxFdtDump()
