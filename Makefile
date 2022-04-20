TESTSOURCES = $(wildcard test*.cc)
TESTS = $(TESTSOURCES:test_%.cc=test%)
SRC := $(wildcard *.cc)
SRC := $(filter-out $(TESTSOURCES), $(SRC))

INC=-I ..

CFLAGS= -Wall -g
CFLAGS+=$(INC)
.PHONY: tests, clean
tests: $(TESTS)

%.test: test_%.cc %.cc %.h
	g++ $(CFLAGS) -o $@ $^
lib.test: test_lib.cc $(SRC)
	g++ $(CFLAGS) -o $@ $^

test%: %.test
	@echo "\033[1;34mTESTING $@\033[0m"
	@./$<; \
	EXIT_CODE=$$?;\
	if [ $$EXIT_CODE -eq 0 ]; \
	then echo "\033[1;32mSUCCESS\033[0m"; \
	else echo "\033[1;31mFAIL\033[0m with exit code $$EXIT_CODE"; \
	fi

test_lib:
	g++ -fPIC --shared ./arena.cc tlsf_lib.cc tlsf.cc -o libtlsf.so

clean:
	rm -f *.test