SUBDIRS = backport mrpeach/binfile iem_tab/src share_mem pmpd nusmuk-utils nusmuk-audio rendu_egregore

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
