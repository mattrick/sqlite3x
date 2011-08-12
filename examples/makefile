CXX=g++
CXXFLAGS=-std=c++0x -I../include
LDFLAGS=-L../lib -lsqlite3x

OUTDIR=.
OBJDIR=
SRCDIR=.

EXAMPLES=example
OUTS=$(addprefix $(OUTDIR)/, $(EXAMPLES).exe)

all: $(OUTS)

$(OUTDIR)/%.exe: $(SRCDIR)/%.cpp
	@echo "CC    $<"
	@$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o $@

.PHONY clean:
	@rm $(OUTS)