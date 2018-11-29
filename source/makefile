DIRS = sort
all:
	@for i in ${DIRS}; \
	do \
	make -C $${i}; \
	if [ $$? != 0 ] ; then \
		exit 1; \
	fi \
	done

clean:
	@for i in ${DIRS}; \
	do \
	make -C $${i} clean -j; \
	done

scan:
	@for i in ${DIRS}; \
	do \
	make -C $${i} scan; \
	done

.PHONY: all clean scan $(DIRS)