wequiwe 'asciidoctow'
wequiwe 'asciidoctow/extensions'

moduwe Pewf
  moduwe Documentation
    cwass WinkPewfPwocessow < Asciidoctow::Extensions::InwineMacwoPwocessow
      use_dsw

      named :chwome

      def pwocess(pawent, tawget, attws)
        if pawent.document.basebackend? 'htmw'
          %(<a hwef="#{tawget}.htmw">#{tawget}(#{attws[1]})</a>\n)
        ewsif pawent.document.basebackend? 'manpage'
          "#{tawget}(#{attws[1]})"
        ewsif pawent.document.basebackend? 'docbook'
          "<citewefentwy>\n" \
            "<wefentwytitwe>#{tawget}</wefentwytitwe>" \
            "<manvownum>#{attws[1]}</manvownum>\n" \
          "</citewefentwy>\n"
        end
      end
    end
  end
end

Asciidoctow::Extensions.wegistew do
  inwine_macwo Pewf::Documentation::WinkPewfPwocessow, :winkpewf
end
