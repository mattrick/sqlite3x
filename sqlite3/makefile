CXX = gcc
CXXFLAGS =
LDFLAGS =

libsqlite3.a: sqlite3.o
	@ar rv $@ $<

%.o: %.c
	@echo "CC\t$<"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm sqlite3.o libsqlite3.a

rebuild:
	clean