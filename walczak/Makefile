include ../config.mk
lflags=-L. `gsl-config --libs`
iflags=`gsl-config --cflags`

# Lists of files to be built
objs=wri-fish.o
src=$(patsubst %.o,%.cc,$(objs))

execs=wf_test

all: $(execs)

executables: $(execs)

-include Makefile.dep

depend:
	$(cxx) $(cflags) $(iflags) -MM $(src) >Makefile.dep

clean:
	rm -rf $(objs) $(execs)

%.o: %.cc
	$(cxx) $(cflags) $(iflags) -c $<

wf_test: wf_test.cc $(objs)
	$(cxx) $(cflags) $(iflags) -o $@ $^ $(lflags)

.PHONY: clean depend
