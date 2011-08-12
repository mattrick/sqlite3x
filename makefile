CXX=g++
CXXFLAGS=-std=c++0x -Isqlite3 -Iinclude -Iinclude/sqlite3x
LDFLAGS=

OUTDIR=lib
OBJDIR=obj
SRCDIR=src

OBJS_LIST=DB.o Query.o Cell.o sqlite3.o
OBJS=$(addprefix $(OBJDIR)/, $(OBJS_LIST))
OUT=$(OUTDIR)/libsqlite3x.a

$(OUT): $(OBJS)
	@mkdir -p $(OUTDIR)
	@echo "AR    $@"
	@ar cr $(OUT) $(OBJS)
	@make -C examples

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CC    $<"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJDIR)/sqlite3.o:
	@make sqlite3.o -C sqlite3

.PHONY clean:
	@rm $(OBJS)
	@rm $(OUT)
	@make -C sqlite3 clean
	@make -C examples clean