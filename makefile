

setup:
	meson setup builddir -Dbuild_test_targets=true -Db_coverage=true

build:
	meson compile -C builddir

remove:
	rm -rf builddir


