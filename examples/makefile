CXX=g++
CXXFLAGS=-std=c++0x -ldl -lpthread -I../include
LDFLAGS=-L../lib -lsqlite3x

OUTDIR=.
OBJDIR=
SRCDIR=.

EXAMPLES=example
OUTS=$(addprefix $(OUTDIR)/, $(EXAMPLES))

all: $(OUTS)

$(OUTDIR)/%.exe: $(SRCDIR)/%.cpp
	@echo "CC    $<"
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o $@

.PHONY clean:
	@rm $(OUTS)
