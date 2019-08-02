
SRC=math.c develop.c matrix.c parser.c contrib.c sockets.c mudlib_stats.c 
OBJ=math.$(O) develop.$(O) matrix.$(O) parser.$(O) contrib.$(O) sockets.$(O) mudlib_stats.$(O) 

OBJ=$(addprefix $(OBJDIR)/,$(subst .c,.o,$(SRC)))

$(OBJDIR)/%.o: %.c
	$(CXX) -I$(OBJDIR) -I.. $(CFLAGS) -o $@ -c $<

all: $(OBJ)
	ar rcu packages.$(A) $(OBJ)
	$(RANLIB) packages.$(A)

$(OBJDIR)/db.o: db.c
	$(CXX) -I$(OBJDIR) -I.. -I/usr/include/mysql $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.$(O)
	rm -f packages.$(A)
