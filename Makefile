CC=			gcc
CXX=		g++
CFLAGS=		#-g -Wall -O2 -m64
CXXFLAGS=	$(CFLAGS)
DFLAGS=		
OBJS=	 object.o user.o exceptions.o utils.o
PROGS=		tests \
			objput objget objlist \
			objsetacl objgetacl objtestacl #assignment 1
INCLUDES=	
LIBS=

.SUFFIXES:.cc .c .o

.c.o:
		$(CC) -c $(CFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@
.cc.o:
		$(CXX) -c $(CXXFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@

#first is default
all:$(PROGS)

tests: $(OBJS) tests.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) tests.o -o $@ $(LIBS)
objput:$(OBJS) objput.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objput.o -o $@ $(LIBS)

objget:$(OBJS) objget.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objget.o -o $@ $(LIBS)

objlist:$(OBJS) objlist.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objlist.o -o $@ $(LIBS)


objsetacl:$(OBJS) objsetacl.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objsetacl.o -o $@ $(LIBS)

objgetacl:$(OBJS) objgetacl.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objgetacl.o -o $@ $(LIBS)	

objtestacl:$(OBJS) objtestacl.o
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(OBJS) objtestacl.o -o $@ $(LIBS)
	
object.o:object.h objectstore.h
user.o:user.h objectstore.h
exceptions.o:exceptions.h objectstore.h
utils.o:utils.h objectstore.h

clean:
	rm -f *.o a.out $(PROGS) *~ *.a