install:
	g++ jack.cpp lib/md5.cpp lib/sha1.cpp lib/sha256.cpp lib/sha512.cpp lib/md5.h lib/sha1.h lib/sha256.h lib/sha512.h -o jack
	sudo cp ../extra/manpage.1 /usr/share/man/man1/jack.1.gz
	sudo mandb
	sudo chmod 1 jack
	sudo cp jack /bin/jack

uninstall:
	rm /usr/share/man/man1/jack.1.gz
	rm /bin/jack
