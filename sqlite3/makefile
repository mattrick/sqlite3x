CXX=gcc
CXXFLAGS=
LDFLAGS=

OUTDIR=../lib
OBJDIR=../obj
SRCDIR=.

OUT=$(OUTDIR)/libsqlite3.a
OBJS=$(OBJDIR)/sqlite3.o

$(OUT): $(OBJS)
	@mkdir -p $(OUTDIR)
	@echo "AR    $@"
	@ar cr $@ $<

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

sqlite3.o: $(SRCDIR)/sqlite3.c | $(OBJDIR)
	@echo "CC    $<"
	@$(CXX) -c $(CXXFLAGS) -o $(OBJS) $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "CC    $<"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

.PHONY clean:
	@rm $(OUT)
	@rm $(OBJS)