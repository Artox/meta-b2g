DESCRIPTION = "A package of M4 macros to produce scripts to \
automatically configure sourcecode."
LICENSE = "GPLv3+-with-Autoconf-Configure-Script-Exception-v3.0"
HOMEPAGE = "http://www.gnu.org/software/autoconf/"
SECTION = "devel"
DEPENDS += "m4-native"
RDEPENDS_${PN} = "m4 perl gnu-config"
DEPENDS_virtclass-native = "m4-native gnu-config-native"
RDEPENDS_${PN}_virtclass-native = "m4-native gnu-config-native"

INC_PR = "r13"

SRC_URI = "${GNU_MIRROR}/autoconf/autoconf-${PV}.tar.bz2;name=autoconf \
	   file://program_prefix.patch"

inherit autotools

# Excluded: tests man doc
SUBDIRS = "bin . lib"

do_configure_prepend () {
	if ${@['true', 'false'][bb.data.inherits_class('native', d)]}
	then
		export ac_cv_path_PERL="${ac_cv_path_PERL=${bindir}/perl}"
		export ac_cv_path_M4="${ac_cv_path_M4=${bindir}/m4}"
		export ac_cv_prog_gnu_m4="${ac_cv_prog_gnu_m4=yes}"
	fi

	sed -i -e's,^SUBDIRS = .*,SUBDIRS = ${SUBDIRS},' ${S}/Makefile.in

	# prevent OE from recreating configure
	rm -fv configure.in
}

do_configure_append() {
	# replace paths to STAGING_BINDIR_NATIVE/perl with ${bindir}/perl
	# sed -i -e "s:#! @PERL@ -w:#! /usr/bin/env perl:" ${S}/bin/*.in
	# why only -w?
	
}

PARALLEL_MAKE = ""
BBCLASSEXTEND = "native"
