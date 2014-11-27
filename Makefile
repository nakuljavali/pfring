all: libpfring pcap ring_examples libzero_examples zc_examples tcpdump lib_c++

###################

libpfring:
	cd lib; ./configure; make

pcap:
	cd libpcap-1.1.1-ring; ./configure --enable-ipv6; make

ring_examples:
	cd examples; make

libzero_examples:
	cd examples_libzero; make

zc_examples:
	cd examples_zc; make

lib_c++:
	cd c++; make

tcpdump:
	cd tcpdump-4.1.1; ./configure ; make

###################

clean: libpfring_clean pcap_clean ring_examples_clean libzero_examples_clean zc_examples_clean lib_c++_clean tcpdump_clean

libpfring_clean:
	cd lib; make clean

pcap_clean:
	if test -f libpcap-1.1.1-ring/config.status; then cd libpcap-1.1.1-ring; make clean; fi

ring_examples_clean:
	cd examples; make clean

libzero_examples_clean:
	cd examples_libzero; make clean

zc_examples_clean:
	cd examples_zc; make clean

lib_c++_clean:
	cd c++; make clean

tcpdump_clean:
	if test -f tcpdump-4.1.1/config.status; then cd tcpdump-4.1.1; make clean; fi
