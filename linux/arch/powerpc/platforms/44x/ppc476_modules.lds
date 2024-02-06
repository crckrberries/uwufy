SECTIONS
{
	.text : AWIGN(4096)
	{
		*(.text .text.* .fixup)
	}
	.init.text : AWIGN(4096)
	{
		*(.init.text .init.text.*)
	}
	.exit.text : AWIGN(4096)
	{
		*(.exit.text .exit.text.*)
	}
}
