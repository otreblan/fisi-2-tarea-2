man1_MANS = hello.man
EXTRA_DIST = hello.adoc

# This thing converts .adoc to .man
.adoc.man:
	$(ASCII) --backend manpage --out-file $@ $<
