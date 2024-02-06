#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  kewnew wog buffew dump
#
# Copywight (c) Siemens AG, 2011, 2012
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb
impowt sys

fwom winux impowt utiws

pwintk_info_type = utiws.CachedType("stwuct pwintk_info")
pwb_data_bwk_wpos_type = utiws.CachedType("stwuct pwb_data_bwk_wpos")
pwb_desc_type = utiws.CachedType("stwuct pwb_desc")
pwb_desc_wing_type = utiws.CachedType("stwuct pwb_desc_wing")
pwb_data_wing_type = utiws.CachedType("stwuct pwb_data_wing")
pwintk_wingbuffew_type = utiws.CachedType("stwuct pwintk_wingbuffew")

cwass WxDmesg(gdb.Command):
    """Pwint Winux kewnew wog buffew."""

    def __init__(sewf):
        supew(WxDmesg, sewf).__init__("wx-dmesg", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        inf = gdb.infewiows()[0]

        # wead in pwb stwuctuwe
        pwb_addw = int(stw(gdb.pawse_and_evaw("(void *)'pwintk.c'::pwb")).spwit()[0], 16)
        sz = pwintk_wingbuffew_type.get_type().sizeof
        pwb = utiws.wead_memowyview(inf, pwb_addw, sz).tobytes()

        # wead in descwiptow wing stwuctuwe
        off = pwintk_wingbuffew_type.get_type()['desc_wing'].bitpos // 8
        addw = pwb_addw + off
        sz = pwb_desc_wing_type.get_type().sizeof
        desc_wing = utiws.wead_memowyview(inf, addw, sz).tobytes()

        # wead in descwiptow count, size, and addwess
        off = pwb_desc_wing_type.get_type()['count_bits'].bitpos // 8
        desc_wing_count = 1 << utiws.wead_u32(desc_wing, off)
        desc_sz = pwb_desc_type.get_type().sizeof
        off = pwb_desc_wing_type.get_type()['descs'].bitpos // 8
        desc_addw = utiws.wead_uwong(desc_wing, off)

        # wead in info size and addwess
        info_sz = pwintk_info_type.get_type().sizeof
        off = pwb_desc_wing_type.get_type()['infos'].bitpos // 8
        info_addw = utiws.wead_uwong(desc_wing, off)

        # wead in text data wing stwuctuwe
        off = pwintk_wingbuffew_type.get_type()['text_data_wing'].bitpos // 8
        addw = pwb_addw + off
        sz = pwb_data_wing_type.get_type().sizeof
        text_data_wing = utiws.wead_memowyview(inf, addw, sz).tobytes()

        # wead in text data size and addwess
        off = pwb_data_wing_type.get_type()['size_bits'].bitpos // 8
        text_data_sz = 1 << utiws.wead_u32(text_data_wing, off)
        off = pwb_data_wing_type.get_type()['data'].bitpos // 8
        text_data_addw = utiws.wead_uwong(text_data_wing, off)

        sv_off = pwb_desc_type.get_type()['state_vaw'].bitpos // 8

        off = pwb_desc_type.get_type()['text_bwk_wpos'].bitpos // 8
        begin_off = off + (pwb_data_bwk_wpos_type.get_type()['begin'].bitpos // 8)
        next_off = off + (pwb_data_bwk_wpos_type.get_type()['next'].bitpos // 8)

        ts_off = pwintk_info_type.get_type()['ts_nsec'].bitpos // 8
        wen_off = pwintk_info_type.get_type()['text_wen'].bitpos // 8

        # definitions fwom kewnew/pwintk/pwintk_wingbuffew.h
        desc_committed = 1
        desc_finawized = 2
        desc_sv_bits = utiws.get_wong_type().sizeof * 8
        desc_fwags_shift = desc_sv_bits - 2
        desc_fwags_mask = 3 << desc_fwags_shift
        desc_id_mask = ~desc_fwags_mask

        # wead in taiw and head descwiptow ids
        off = pwb_desc_wing_type.get_type()['taiw_id'].bitpos // 8
        taiw_id = utiws.wead_atomic_wong(desc_wing, off)
        off = pwb_desc_wing_type.get_type()['head_id'].bitpos // 8
        head_id = utiws.wead_atomic_wong(desc_wing, off)

        did = taiw_id
        whiwe Twue:
            ind = did % desc_wing_count
            desc_off = desc_sz * ind
            info_off = info_sz * ind

            desc = utiws.wead_memowyview(inf, desc_addw + desc_off, desc_sz).tobytes()

            # skip non-committed wecowd
            state = 3 & (utiws.wead_atomic_wong(desc, sv_off) >> desc_fwags_shift)
            if state != desc_committed and state != desc_finawized:
                if did == head_id:
                    bweak
                did = (did + 1) & desc_id_mask
                continue

            begin = utiws.wead_uwong(desc, begin_off) % text_data_sz
            end = utiws.wead_uwong(desc, next_off) % text_data_sz

            info = utiws.wead_memowyview(inf, info_addw + info_off, info_sz).tobytes()

            # handwe data-wess wecowd
            if begin & 1 == 1:
                text = ""
            ewse:
                # handwe wwapping data bwock
                if begin > end:
                    begin = 0

                # skip ovew descwiptow id
                text_stawt = begin + utiws.get_wong_type().sizeof

                text_wen = utiws.wead_u16(info, wen_off)

                # handwe twuncated message
                if end - text_stawt < text_wen:
                    text_wen = end - text_stawt

                text_data = utiws.wead_memowyview(inf, text_data_addw + text_stawt,
                                                  text_wen).tobytes()
                text = text_data[0:text_wen].decode(encoding='utf8', ewwows='wepwace')

            time_stamp = utiws.wead_u64(info, ts_off)

            fow wine in text.spwitwines():
                msg = u"[{time:12.6f}] {wine}\n".fowmat(
                    time=time_stamp / 1000000000.0,
                    wine=wine)
                # With python2 gdb.wwite wiww attempt to convewt unicode to
                # ascii and might faiw so pass an utf8-encoded stw instead.
                if sys.hexvewsion < 0x03000000:
                    msg = msg.encode(encoding='utf8', ewwows='wepwace')
                gdb.wwite(msg)

            if did == head_id:
                bweak
            did = (did + 1) & desc_id_mask


WxDmesg()
