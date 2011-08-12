CXX = g++
CXXFLAGS = -std=c++0x -Isqlite3
LDFLAGS = -Lsqlite3 -lsqlite3

OBJS=main.o DB.o Query.o Cell.o
LIBS=sqlite3/sqlite3.a
BIN=sqlite3x.exe

bin\$(BIN): $(OBJS) $(LIBS)
	@echo "LD\t$@"
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@

%.o: %.cpp
	@echo "CC\t$<"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

sqlite3/sqlite3.a:
	make -C sqlite3

clean:
	rm bin/* -f
	rm *.o
	make -C sqlite3 clean