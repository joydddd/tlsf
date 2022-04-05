TESTSOURCES = $(wildcard test*.cc)

INC=-I ..

CFLAGS= -Wall
CFLAGS+=$(INC)

test_%: test_%.cc %.cc %.h
	g++ $(CFLAGS) -o $@ $^
